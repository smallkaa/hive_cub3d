/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pavel Vershinin <pvershin@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:50 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/27 20:29:44 by Pavel Versh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** @brief      Initializes the camera's orientation and field of view.
** @details    1. Converts the player's viewing angle from degrees to radians.
** 2. Calculates the direction vectors (dirx, diry) based on the
** angle. This vector points from the player's position forward.
** 3. Calculates the camera plane vectors (plx, ply), which are
** perpendicular to the direction vector. The length of the
** plane vector determines the field of view (FOV).
*/
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

/*
** @brief      Sets up the initial step and side distances for the DDA algorithm.
** @details    1. Determines the step direction (stepx, stepy) as either +1 or
** -1 based on the ray's direction (rx, ry).
** 2. Calculates the initial distance (sx, sy) from the player's
** position to the first vertical (x-side) and horizontal
** (y-side) grid lines. This is the starting point for the DDA.
*/
static void	init_dda_step(t_ray *r)
{
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

/*
** @brief      Initializes a ray's properties for a specific screen column (x).
** @details    1. Calculates the camera's x-coordinate on the camera plane,
** ranging from -1 for the left edge to +1 for the right edge.
** 2. Determines the ray's direction vector (rx, ry) for the given
** screen column.
** 3. Sets the ray's starting map coordinates (mapx, mapy).
** 4. Calculates the distance the ray has to travel to cross one
** full unit in the x or y direction (dx, dy).
** 5. Calls `init_dda_step` to set up initial DDA parameters.
*/
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
	init_dda_step(r);
}

/*
** @brief      Executes the Digital Differential Analysis (DDA) algorithm.
** @details    1. Steps through the grid, moving one square at a time, until it
** hits a wall.
** 2. In each step, it checks whether the next vertical grid line
** (x-side) or the next horizontal grid line (y-side) is closer.
** 3. Advances the ray to the closer grid line and updates the map
** coordinates (mapx or mapy).
** 4. After a wall is hit, calculates the perpendicular distance
** (perp) from the player to the wall to avoid a fisheye effect.
*/
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
** The main rendering function that casts a ray for each screen column.
*/
void	render_view(t_game *g)
{
	int		x;
	t_ray	r;

	ft_memset(&r, 0, sizeof(t_ray));
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
