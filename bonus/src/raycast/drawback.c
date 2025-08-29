/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvershin <pvershin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:25 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/29 12:57:47 by pvershin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
** @brief      Fills the screen with the ceiling and floor colors.
** @details    This function is responsible for drawing the static background
** of the scene, which consists of a solid color for the
** ceiling and another for the floor. It is typically called
** at the beginning of each frame's rendering process.
**
** 1. **Draw the Ceiling:**
** - It iterates through every pixel in the top half of the
** screen (from y = 0 to the vertical midpoint).
** - For each pixel, it calls `mlx_put_pixel` to paint it with
** the predefined ceiling color (`game->map->ceil_c`).
**
** 2. **Draw the Floor:**
** - It then continues iterating from the vertical midpoint to
** the bottom of the screen.
** - For each pixel in this bottom half, it paints the
** predefined floor color (`game->map->floor_c`).
**
** This process efficiently establishes the basic sky and ground
** before the more complex wall textures are drawn over them.
*/
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->ceil_c);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->floor_c);
			x++;
		}
		y++;
	}
}

/*
** @brief      Checks if a given coordinate (x, y) on the map is a wall.
** @details    1. Verifies if the y-coordinate is within the map's height.
** 2. Verifies if the x-coordinate is within the width of the
** corresponding row.
** 3. Returns 1 (true) if the coordinate is out of bounds or if the
** character at that position is '1' (a wall) or ' ' (empty
** space, also treated as a wall).
** 4. Returns 0 (false) otherwise.
*/
int	map_is_wall(t_map *m, int x, int y)
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
