#include "cub3D.h"

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
	s->y0 = -s->height / 2 + WINDOW_HEIGHT / 2;
	s->y1 = s->height / 2 + WINDOW_HEIGHT / 2;
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

void	draw_stripe(t_game *g, int x, t_ray *r)
{
	t_stripe_data	s;

	init_stripe(g, r, &s);
	if (!s.tex)
		return ;
	draw_texture_column(g, &s, x);
}