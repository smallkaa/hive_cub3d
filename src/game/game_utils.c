#include "cub3D.h"


void convert_hero_to_pixels(t_map *map)
{
	map->hero.x = map->hero.x * TILE_SIZE + TILE_SIZE / 2;
	map->hero.y = map->hero.y * TILE_SIZE + TILE_SIZE / 2;
}