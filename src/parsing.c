#include "cub3D.h"

int	name_validation(char *filename)
{
	char	*extension;
	int		len;

	len = ft_strlen(filename);
	if (len < 5)
		return (-1);
	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".cub", len) != 0)
		return (-1);
	return (1);
}




t_map	*parsing_args(char *filename)
{
	t_map	*map;
	int		map_start;
	int i = 0;

	//printf("→ Validating name\n");
	if (name_validation(filename) < 0)
		return (err_msg("wrong file name"), NULL);

	//printf("→ Allocating map struct\n");
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (err_msg("memory error"), NULL);

	//printf("→ Counting lines\n");
	map->size_y = count_lines(filename);
	if (map->size_y < 1)
	{
		free(map);
		err_msg("error file reading");
		return (NULL);
	}
		

	//printf("→ Allocating map->area (%d lines)\n", map->size_y);
	map->area = ft_calloc(map->size_y + 1, sizeof(char *));
	if (!map->area)
	{
		free_map(map);
		err_msg("memory error");
		return (NULL);
	}
		
	if (read_map(map, filename, map->size_y + 1, 0) < 0)
	{
		if (map->area)
			free(map);
		free(map);
		err_msg("read map failed");
		return (NULL);
	}
	// ✅ Init color sentinels
	map->floor_c = 0xFFFFFFFF;
	map->ceil_c = 0xFFFFFFFF;

	// ✅ Parse config identifiers before the map starts
	while (map->area[i])
	{
		if (is_map_line(map->area[i]))
			break;
		else if (map->area[i][0] != '\0' && map->area[i][0] != '\n')
		{
			if (!parse_identifier_line(map, map->area[i]))
			{
				free_map(map);
				return (err_msg("Error: invalid identifier line"), NULL);
			}
		}
		i++;
	}

	// ✅ Check all required textures and colors are present
	if (!map->no || !map->so || !map->we || !map->ea ||
		map->floor_c == 0xFFFFFFFF || map->ceil_c == 0xFFFFFFFF)
	{
		free_map(map);
		return (err_msg("Error: missing texture or color"), NULL);
	}

	// ✅ Start map parsing from detected index
	map_start = i;
	if (symbols_check(map, map_start) < 0 || player_check(map, map_start) < 0 )
	{
		free_map(map);
		return (NULL);
	}
	printf("LINE[%d]: %s\n", i, map->area[i]);
	printf("Map parsed successfully\n");
	return (map);
}

