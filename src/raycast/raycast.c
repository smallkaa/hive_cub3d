#include "cub3D.h"

/* Tiny epsilon for divisions */
#define BIG_NUM 1e30
#define FOV_DEG 60.0
#define CAMERA_PITCH 90

/* Return 1 if outside or wall/void, else 0 */
static int	map_is_wall(t_map *m, int x, int y)
{
	size_t	len;

	if (y < 0 || y >= m->size_y || !m->area[y])
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
	r->dx = BIG_NUM;
	if (r->rx != 0.0)
		r->dx = fabs(1.0 / r->rx);
	r->dy = BIG_NUM;
	if (r->ry != 0.0)
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

/*
** Calculates the texture's X coordinate based on the wall hit data.
*/
static int	calculate_texture_x(t_ray *r, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = r->posy + r->perp * r->ry;
	else
		wall_x = r->posx + r->perp * r->rx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (r->side == 0 && r->rx > 0)
		tex_x = tex->width - tex_x - 1;
	if (r->side == 1 && r->ry < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	init_stripe(t_game *g, t_ray *r, t_stripe_data *s)
{
	s->height = (int)((double)WINDOW_HEIGHT / r->perp);
	s->y0 = -s->height / 2 + WINDOW_HEIGHT / 2 - CAMERA_PITCH;
	s->y1 = s->height / 2 + WINDOW_HEIGHT / 2 - CAMERA_PITCH;
	s->face = pick_face(r);
	s->tex = g->tx.tex[s->face];
	s->tex_x = calculate_texture_x(r, s->tex);
}

static void	draw_texture_column(t_game *g, t_stripe_data *s, int x)
{
	double		tex_pos;
	double		tex_step;
	int			y;
	int			tex_y;
	uint32_t	color;

	tex_step = 1.0 * s->tex->height / s->height;
	tex_pos = 0.0;
	if (s->y0 < 0)
		tex_pos = -s->y0 * tex_step;
	y = s->y0;
	if (y < 0)
		y = 0;
	while (y <= s->y1 && y < WINDOW_HEIGHT)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)s->tex->height)
			tex_y = s->tex->height - 1;
		color = get_texture_pixel(s->tex, s->tex_x, tex_y);
		mlx_put_pixel(g->img, x, y, color);
		tex_pos += tex_step;
		y++;
	}
}

static void	draw_stripe(t_game *g, int x, t_ray *r)
{
	t_stripe_data	s;

	init_stripe(g, r, &s);
	if (!s.tex)
		return ;
	draw_texture_column(g, &s, x);
}

/*
** The main rendering function that casts a ray for each screen column.
*/
void	render_view(t_game *g)
{
	int		x;
	t_ray	r;
	
	ft_memset(&r, 0, sizeof(t_ray));
	// r.posx = g->map->hero.x + 0.5;
	// r.posy = g->map->hero.y + 0.5;
	// transfer to pixels
	r.posx = g->map->hero.x / TILE_SIZE;
	r.posy = g->map->hero.y / TILE_SIZE;
	init_camera(g, &r);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray_for_x(&r, x);
		perform_dda(g, &r);
		draw_stripe(g, x, &r);
		x++;
	}
}