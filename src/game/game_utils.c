/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pavel Vershinin <pvershin@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:27:54 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/27 21:23:31 by Pavel Versh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	convert_hero_to_pixels(t_map *map)
{
	map->hero.x = map->hero.x * TILE_SIZE + TILE_SIZE / 2;
	map->hero.y = map->hero.y * TILE_SIZE + TILE_SIZE / 2;
}

int	check_collision(t_game *g, double new_x, double new_y)
{
	int tx0 = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	int ty0 = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	int tx1 = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	int ty1 = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);

	if (map_is_wall(g->map, tx0, ty0)) return (0);
	if (map_is_wall(g->map, tx1, ty0)) return (0);
	if (map_is_wall(g->map, tx0, ty1)) return (0);
	if (map_is_wall(g->map, tx1, ty1)) return (0);
	return (1);
}
