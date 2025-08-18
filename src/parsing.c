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

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (err_msg("file openning error 1"), -1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static int read_map(t_map *map, const char *filename, int max_lines, int i)
{
	int   fd;
	char *line;
	char *nl;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (err_msg("file opening error 2"), -1);

	while (i < max_lines)
	{
		line = get_next_line(fd);
		if (!line)
			break;

		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		if (i >= max_lines) 
		{
   			close(fd);
			return (err_msg("too many lines"), -1);
		}
		map->area[i] = ft_strdup(line);
		free(line);
		if (!map->area[i])
		{
			close(fd);
			free_area(map->area, i);
			map->area = NULL;
			return (err_msg("memory error"), -1);
		}
		i++;
	}
	close(fd);
	map->area[i] = NULL;
 
	return (1);
}


t_map	*parsing_args(char *filename)
{
	t_map	*map;

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
		return (free(map), err_msg("error file reading"), NULL);

	//printf("→ Allocating map->area (%d lines)\n", map->size_y);
	map->area = ft_calloc(map->size_y + 1, sizeof(char *));
	if (!map->area)
		return (free_map(map), err_msg("memory error"), NULL);
	if (read_map(map, filename, map->size_y + 1, 0) < 0)
	{
		if (map->area)
			free(map);
		free(map);
		err_msg("read map failed");
		return (NULL);
	}
	//printf("Map parsed successfully\n");
	return (map);
}

