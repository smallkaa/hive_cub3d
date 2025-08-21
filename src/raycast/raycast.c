#include "cub3D.h"

/* Tiny epsilon for divisions */
#define BIG_NUM 1e30
#define FOV_DEG 60.0

/* Return 1 if outside or wall/void, else 0 */
static int	map_is_wall(t_map *m, int x, int y)
{
	size_t	len;

	if (y < 0 || y >= m->size_y)
		return (1);
	if (!m->area[y])
		return (1);
	len = ft_strlen(m->area[y]);
	if (x < 0 || (size_t)x >= len)
		return (1);
	if (m->area[y][x] == '1' || m->area[y][x] == ' ')
		return (1);
	return (0);
}

/* Build camera basis from hero angle (0=N, 90=E, ...). */
static void	init_camera(t_game *g, t_ray *r)
{
	double	theta;
	double	scale;

	scale = tan((FOV_DEG * M_PI / 180.0) / 2.0);
	theta = g->map->hero.angle * M_PI / 180.0;
	r->dirx = sin(theta);
	r->diry = -cos(theta);
	r->plx = r->diry * scale;
	r->ply = -r->dirx * scale;
}

/* Initialize ray for screen column x. */
static void	init_ray_for_x(t_ray *r, int x)
{
	double	cx;

	cx = (2.0 * (double)x / (double)WINDOW_WIDTH) - 1.0;
	r->rx = r->dirx + r->plx * cx;
	r->ry = r->diry + r->ply * cx;
	r->mapx = (int)r->posx;
	r->mapy = (int)r->posy;
	if (r->rx == 0.0)
		r->dx = BIG_NUM;
	else
		r->dx = fabs(1.0 / r->rx);
	if (r->ry == 0.0)
		r->dy = BIG_NUM;
	else
		r->dy = fabs(1.0 / r->ry);
	if (r->rx < 0)
	{
		r->stepx = -1;
		r->sx = (r->posx - r->mapx) * r->dx;
	}
	else
	{
		r->stepx = 1;
		r->sx = (r->mapx + 1.0 - r->posx) * r->dx;
	}
	if (r->ry < 0)
	{
		r->stepy = -1;
		r->sy = (r->posy - r->mapy) * r->dy;
	}
	else
	{
		r->stepy = 1;
		r->sy = (r->mapy + 1.0 - r->posy) * r->dy;
	}
}

/* Classic DDA to find the first wall hit. */
static void	perform_dda(t_game *g, t_ray *r)
{
	while (!map_is_wall(g->map, r->mapx, r->mapy))
	{
		if (r->sx < r->sy)
		{
			r->sx += r->dx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sy += r->dy;
			r->mapy += r->stepy;
			r->side = 1;
		}
	}
	if (r->side == 0)
		r->perp = (r->mapx - r->posx + (1 - r->stepx) / 2.0) / r->rx;
	else
		r->perp = (r->mapy - r->posy + (1 - r->stepy) / 2.0) / r->ry;
	if (r->perp < 1e-6)
		r->perp = 1e-6;
}

static void	draw_wall_pixel(t_game *g, t_pixel_data *pixel, t_ray *r)
{
	t_face			face;
	mlx_texture_t	*texture;
	int				tex_x;
	int				tex_y;
	uint32_t		color;

	face = pick_face(r);
	texture = g->tx.tex[face];
	if (!texture)
	{
		color = 0xFF9E9E9E;
		if (r->side == 1)
			color = 0xFF6E6E6E;
	}
	else
	{
		tex_x = (pixel->x * texture->width) / WINDOW_WIDTH;
		tex_y = ((pixel->y - pixel->y0) * texture->height) / (pixel->y1 - pixel->y0 + 1);
		if (tex_x >= (int)texture->width)
			tex_x = texture->width - 1;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		color = get_texture_pixel(texture, tex_x, tex_y);
	}
	mlx_put_pixel(g->img, pixel->x, pixel->y, color);
}
/* Draw one vertical stripe for the hit. */
// static void	draw_stripe(t_game *g, int x, t_ray *r)
// {
// 	int			line_h;
// 	int			y0;
// 	int			y1;
// 	uint32_t	col;
// 	int			y;

// 	line_h = (int)((double)WINDOW_HEIGHT / r->perp);
// 	y0 = -line_h / 2 + WINDOW_HEIGHT / 2;
// 	if (y0 < 0)
// 		y0 = 0;
// 	y1 = line_h / 2 + WINDOW_HEIGHT / 2;
// 	if (y1 >= WINDOW_HEIGHT)
// 		y1 = WINDOW_HEIGHT - 1;
// 	col = 0xFF9E9E9E;
// 	if (r->side == 1)
// 		col = 0xFF6E6E6E;
// 	y = y0;
// 	while (y <= y1)
// 	{
// 		mlx_put_pixel(g->img, x, y, col);
// 		y++;
// 	}
// }

static void	draw_stripe(t_game *g, int x, t_ray *r)
{
	int			line_h;
	int			y0;
	int			y1;
	int			y;
	t_pixel_data pixel;

	line_h = (int)((double)WINDOW_HEIGHT / r->perp);
	y0 = -line_h / 2 + WINDOW_HEIGHT / 2;
	if (y0 < 0)
		y0 = 0;
	y1 = line_h / 2 + WINDOW_HEIGHT / 2;
	if (y1 >= WINDOW_HEIGHT) 
		y1 = WINDOW_HEIGHT - 1;
	pixel.x = x;
	pixel.y0 = y0;
	pixel.y1 = y1;
	y = y0;
	while (y <= y1)
	{
		pixel.y = y;
		draw_wall_pixel(g, &pixel, r);  // 4 args exactly
		y++;
	}
}

/* Public entry: render walls once from the spawn point. */
void	render_view(t_game *g)
{
	int		x;
	t_ray	r;

	ft_memset(&r, 0, sizeof(t_ray));
	r.posx = g->map->hero.x + 0.5;
	r.posy = g->map->hero.y + 0.5;
	init_camera(g, &r);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_for_x(&r, x); // Cast ray for column x from player position
		perform_dda(g, &r);    // find wall distance
		draw_stripe(g, x, &r); // draw stripe at column x
		x++;
	}
}
