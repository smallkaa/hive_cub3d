#include "cub3D.h"

bool	is_map_line(const char *line)
{
	int	i;
	bool	has_map_char = false;

	i = 0;
	while (line[i])
	{
		if (!is_valid_symbol(line[i]) && line[i] != '\n')
			return false;
		if (line[i] == '1' || line[i] == '0')
			has_map_char = true;
		i++;
	}
	return has_map_char;
}

int	find_map_start(t_map *map)
{
	int	i;

	i = 0;
	while (map->area[i])
	{
		if (is_map_line(map->area[i]))
			return (i);
		i++;
		//printf("map start check %d\n", i);
	}
	printf("map start check %d\n", i);
	return (-1);
}

int	symbols_check(t_map *map, int map_start)
{
	int		x;
	int		y;

	y = map_start;
	//printf("map start symbol check %d\n", y);
	// if (!map || !map->area || !map->area[y])
	// 	return (err_msg("Error: map->area is NULL"), -1);
	while (map->area[y])
	{
		x = 0;
		
		while (map->area[y][x])
		{
			if (!is_valid_symbol(map->area[y][x]))
				return (err_msg("Error: Wrong symbol found"), -1);
			x++;
		}
		y++;
	}
	return (1);
}
int process_hero_coordinates(t_map *map, int x, int y)
{
	if (map->area[y][x] == 'N' || map->area[y][x] == 'S'
		|| map->area[y][x] == 'E' || map->area[y][x] == 'W')
	{
		map->hero.x = x;
		map->hero.y = y;
		if(map->area[y][x] == 'N')
			map->hero.angle = 0;
		else if (map->area[y][x] == 'S')
			map->hero.angle = 180;
		else if (map->area[y][x] == 'E')
			map->hero.angle = 90;
		else if (map->area[y][x] == 'W')
			map->hero.angle = 270;
		return (1);
	}
	return (0);
}

int player_check(t_map *map, int map_start)
{
	int	x;
	int y;
	int player_count = 0;

	y = map_start;
	// if (!map || !map->area || !map->area[y])
	// 	return (err_msg("Error: map->area is NULL"), -1);
	while(map->area[y])
	{
		x = 0;
		while (map->area[y][x])
		{
			player_count += process_hero_coordinates(map, x, y);
			x++; // increment column
		}
		y++; // increment row
	}
	if (player_count != 1)
		return (err_msg("Error: There must be exactly one player (N/S/E/W)"), -1);
	return (1);
}
