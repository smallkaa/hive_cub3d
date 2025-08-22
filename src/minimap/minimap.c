#include "minimap.h"


// safe put_pixel (clamped)
static inline void mm_put(mlx_image_t *img, int x, int y, uint32_t c)
{
	if ((unsigned)x < img->width && (unsigned)y < img->height)
		mlx_put_pixel(img, x, y, c);
}

int minimap_init(t_game *g, t_minimap *mm)
{
	// total pixels needed from map size
	mm->w = g->map->size_x * MM_TILE;
	mm->h = g->map->size_y * MM_TILE;

	// keep it on screen even for big maps (optional: clip to max size)
	// If you want clipping, you can compute min(width, some_limit).

	mm->ox = MM_MARGIN_X;
	mm->oy = MM_MARGIN_Y;

	mm->img = mlx_new_image(g->mlx, mm->w, mm->h);
	if (!mm->img)
		return (err_msg("minimap: mlx_new_image failed"), -1);

	// Add once; we’ll just repaint pixels inside it every frame
	if (mlx_image_to_window(g->mlx, mm->img, mm->ox, mm->oy) < 0)
		return (err_msg("minimap: image_to_window failed"), -1);

	// draw first frame now
	minimap_draw(g, mm);
	return 0;
}

void minimap_draw(t_game *g, t_minimap *mm)
{
	// Colors (ARGB)
	const uint32_t col_bg   = MM_ALPHA(120,  10,  10,  25); // semi‑transparent background
	const uint32_t col_wall = MM_ALPHA(255,  60,  60,  70);
	const uint32_t col_void = MM_ALPHA(80,   15,  15,  20); // outside map spaces
	const uint32_t col_floor= MM_ALPHA(80,   25,  25,  35);
	const uint32_t col_me   = MM_ALPHA(255, 230, 220,  40); // player dot
	const uint32_t col_dir  = MM_ALPHA(255, 250, 240, 140); // facing line

	// Clear (semi‑transparent)
	for (int y = 0; y < mm->h; ++y)
		for (int x = 0; x < mm->w; ++x)
			mlx_put_pixel(mm->img, x, y, col_bg);

	// Draw map cells as blocks of MM_TILE x MM_TILE
	for (int my = 0; my < g->map->size_y; ++my)
	{
		const char *row = g->map->area[my];
		int rowlen = row ? (int)ft_strlen(row) : 0;

		for (int mx = 0; mx < g->map->size_x; ++mx)
		{
			uint32_t c = col_void;
			char cell = (mx < rowlen && row) ? row[mx] : ' '; // outside row -> void

			if (cell == '1')
				c = col_wall;
			else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				c = col_floor;
			else if (cell == ' ')
				c = col_void;

			int px0 = mx * MM_TILE;
			int py0 = my * MM_TILE;
			for (int yy = 0; yy < MM_TILE; ++yy)
				for (int xx = 0; xx < MM_TILE; ++xx)
					mm_put(mm->img, px0 + xx, py0 + yy, c);
		}
	}

	// Player dot
	double px = g->map->hero.x * MM_TILE;
	double py = g->map->hero.y * MM_TILE;

	// small 3x3 dot
	for (int dy = -1; dy <= 1; ++dy)
		for (int dx = -1; dx <= 1; ++dx)
			mm_put(mm->img, (int)(px + dx), (int)(py + dy), col_me);

	// Facing line
	double rad = g->map->hero.angle * M_PI / 180.0;
	double ex = px + cos(rad + M_PI_2) * MM_FOV_LEN; // NOTE: your forward uses sin/cos swapped
	double ey = py + sin(rad + M_PI_2) * MM_FOV_LEN; // rotate 90° to match your forward vector

	// simple DDA for the small line
	int steps = (int)fmax(fabs(ex - px), fabs(ey - py));
	if (steps < 1) steps = 1;
	double stepx = (ex - px) / steps;
	double stepy = (ey - py) / steps;
	double cx = px, cy = py;
	for (int i = 0; i <= steps; ++i)
	{
		mm_put(mm->img, (int)cx, (int)cy, col_dir);
		cx += stepx; cy += stepy;
	}
}
