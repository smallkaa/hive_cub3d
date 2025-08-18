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

	return (0);
}
