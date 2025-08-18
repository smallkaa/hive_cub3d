#include "cub3D.h"

// strncmp with CO NO ......

static char	*dup_trim_path(const char *line)
{
	size_t	n;
	char	*new_line;

	while (*line == ' ' || *line == '\t')
		line++;
	n = ft_strlen(line);
	while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == ' '
		|| line[n - 1] == '\t' || line[n - 1] == '\r'))
		n--;
	if (n == 0)
		return (NULL);
	new_line = malloc(n + 1);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, line, n);
	new_line[n] = '\0';
	return (new_line);
}

static int	set_path(char **dst, const char *rhs)
{
	if (*dst)
	{
		err_msg("Error: duplicate texture");
		return (0);
	}
	*dst = dup_trim_path(rhs);
	return (*dst != NULL);
}
int	parse_identifier_line(t_map *map, const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (!ft_strncmp(line, "NO", 2) && ft_isspace((unsigned char)line[2]))
		return (set_path(&map->no, line + 2));
	if (!ft_strncmp(line, "SO", 2) && ft_isspace((unsigned char)line[2]))
		return (set_path(&map->so, line + 2));
	if (!ft_strncmp(line, "WE", 2) && ft_isspace((unsigned char)line[2]))
		return (set_path(&map->we, line + 2));
	if (!ft_strncmp(line, "EA", 2) && ft_isspace((unsigned char)line[2]))
		return (set_path(&map->ea, line + 2));
	return (0);
}

