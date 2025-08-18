#include "cub3D.h"

bool if_hero(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool if_valid_symbol(char c)
{
	return (c == '0' || c == '1' || c == ' ' || if_hero(c));
}

int	find_map_start(t_map *map)
{
	int	i;

	i = 0;
	while (map->area[i])
	{
		if (map->area[i][0] == '1' || map->area[i][0] == '0'
			|| if_hero(map->area[i][0]) || map->area[i][0] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

int	symbols_check(t_map *map, int map_start)
{
	int		x;
	int		y;

	y = map_start;
	while (map->area[y])
	{
		x = 0;
		
		while (map->area[y][x])
		{
			if (!if_valid_symbol(map->area[y][x]))
				return (err_msg("Error: Wrong symbol found"), -1);
			x++;
		}
		y++;
	}
	return (1);
}