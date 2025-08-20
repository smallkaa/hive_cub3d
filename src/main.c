#include "cub3D.h"

int	main(int ac, char **av)
{
	t_map *map;
	
	//t_game *game;

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
	printf("Player position x- %f y - %f\n", map->hero.x, map->hero.y);
	for(int i = 0; map->area[i]; i++)
		printf("%s\n", map->area[i]);
	return (0);
}
