/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:27:54 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/28 13:15:11 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** @brief      Converts hero position from tile coordinates to pixel coordinates.
**
** @details    Initially, the hero's position (x,
	y) is stored in **tile coordinates**
**             (i.e., indexes on the map grid). But for rendering and collision
**             detection, we need **pixel precision**.
**
**             This function converts tile position to pixel position by:
**             - Multiplying the tile index by TILE_SIZE to get pixel offset.
**             - Adding TILE_SIZE / 2 to center the hero within the tile.
**
** @note       This is essential for raycasting, movement, and minimap rendering
**             to work correctly, as those systems operate on pixel-level math.
*/
void	convert_hero_to_pixels(t_map *map)
{
	map->hero.x = map->hero.x * TILE_SIZE + TILE_SIZE / 2;
	map->hero.y = map->hero.y * TILE_SIZE + TILE_SIZE / 2;
}

/*
** @brief      Checks for collision at a new (x,
	y) position using a bounding box.
**
** @details    1. Calculates four surrounding tile positions based on a small
**             collision buffer to represent the player's physical space.
**             2. Converts the buffered coordinates to tile indices 
**                using TILE_SIZE.
**             3. Uses map_is_wall() to determine if any of the four corners
**             (top-left, top-right, bottom-left, bottom-right) are walls.
**
** @return     0 if any of the corners collide with a wall (movement blocked),
**             1 if all corners are free (movement allowed).
*/
int	check_collision(t_game *g, double new_x, double new_y)
{
	int	tx0;
	int	ty0;
	int	tx1;
	int	ty1;

	tx0 = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	ty0 = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	tx1 = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	ty1 = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);
	if (map_is_wall(g->map, tx0, ty0))
		return (0);
	if (map_is_wall(g->map, tx1, ty0))
		return (0);
	if (map_is_wall(g->map, tx0, ty1))
		return (0);
	if (map_is_wall(g->map, tx1, ty1))
		return (0);
	return (1);
}

void	free_resources(t_game *game)
{
	int	i;

	i = 0;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->wand)
		mlx_delete_image(game->mlx, game->wand);
	while (i < 4)
	{
		if (game->tx.tex[i])
			mlx_delete_texture(game->tx.tex[i]);
		i++;
	}
}

void	close_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tx.tex[i])
			mlx_delete_texture(game->tx.tex[i]);
		i++;
	}
}
