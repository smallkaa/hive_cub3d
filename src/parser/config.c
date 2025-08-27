#include "cub3D.h"

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

static int	parse_number(const char *str, int *i)
{
	int	num;

	num = 0;
	*i = skip_spaces(str, *i);
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		num = num * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (num);
}

uint32_t	parse_color(const char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = parse_number(str, &i);
	if (r < 0 || r > 255 || str[i++] != ',')
		return (err_msg("bad color"), 0xFFFFFFFF);
	g = parse_number(str, &i);
	if (g < 0 || g > 255 || str[i++] != ',')
		return (err_msg("bad color"), 0xFFFFFFFF);
	b = parse_number(str, &i);
	if (b < 0 || b > 255)
		return (err_msg("bad color"), 0xFFFFFFFF);
	i = skip_spaces(str, i);
	if (str[i] != '\0' && str[i] != '\n')
		return (0xFFFFFFFF);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static int	set_path(char **dst, const char *rhs)
{
	if (*dst)
	{
		err_msg("duplicate texture");
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
	if (line[0] == 'F' && ft_isspace((unsigned char)line[1]))
	{
		if (map->floor_c != 0xFFFFFFFF)
			return (err_msg("duplicate floor color"), 0);
		map->floor_c = parse_color(line + 1);
		return (map->floor_c != 0xFFFFFFFF);
	}
	if (line[0] == 'C' && ft_isspace((unsigned char)line[1]))
	{
		if (map->ceil_c != 0xFFFFFFFF)
			return (err_msg("duplicate ceiling color"), 0);
		map->ceil_c = parse_color(line + 1);
		return (map->ceil_c != 0xFFFFFFFF);
	}
	return (0);
}
