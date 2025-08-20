#include "cub3D.h"

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

int read_map(t_map *map, const char *filename, int max_lines, int i)
{
	int		fd;
	char	*line;
	char	*nl;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (err_msg("file openning error 2"), -1);
	while (i < max_lines)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		map->area[i] = ft_strdup(line);
		free(line);
		if (!map->area[i])
			return (close(fd), err_msg("memory error"), -1);
		i++;
	}
	close(fd);
	if (i < max_lines)
		map->area[i] = NULL;
	return (i);
}
