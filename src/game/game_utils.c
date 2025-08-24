#include "cub3D.h"


void convert_hero_to_pixels(t_map *map)
{
	map->hero.x = map->hero.x * TILE_SIZE + TILE_SIZE / 2;
	map->hero.y = map->hero.y * TILE_SIZE + TILE_SIZE / 2;
}

int	check_collision(t_game *game, double new_x, double new_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1')
		return (0);
	tile_x = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1')
		return (0);
	tile_x = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1')
		return (0);
	tile_x = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1')
		return (0);
	return (1);
}