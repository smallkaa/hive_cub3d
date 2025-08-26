#include "cub3D.h"

void print_hero_debug(t_map *map)
{
	printf("Hero at: x = %.2f, y = %.2f (tile: %d, %d)\n",
		map->hero.x, map->hero.y,
		(int)(map->hero.x / TILE_SIZE),
		(int)(map->hero.y / TILE_SIZE));
}
int	main(int ac, char **av)
{
	t_map *map;
	
	t_game game;

	printf("Starting parsing...\n");
	if (ac != 2)
	{
		return (err_msg("Usage: ./cub3d <file.cub>"), 1);
	}
	map = parsing_args(av[1]);
	 if (!map)
		return (1);
	printf("NO: %s\n", map->no);
	printf("SO: %s\n", map->so);
	printf("WE: %s\n", map->we);
	printf("EA: %s\n", map->ea);
	printf("Floor color: %u\n", map->floor_c);
	printf("Ceil color: %u\n", map->ceil_c);
	printf("map size %d\n", map->size_y);
	printf("Player position x- %f y - %f\n, angle - %f\n", map->hero.x, map->hero.y, map->hero.angle);
	for(int i = 0; map->area[i]; i++)
		printf("%s\n", map->area[i]);
	convert_hero_to_pixels(map);
	print_hero_debug(map);
	game.map = map;
	if (game_loop(&game) < 0)
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}
