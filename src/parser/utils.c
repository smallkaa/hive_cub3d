#include "cub3D.h"

void	err_msg(char *msg)
{
	int	len;

	len = 0;
	if (!msg)
		return ;
	while (msg[len] != '\0')
		len++;
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
}

bool	is_valid_symbol(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E');
}

int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

void	free_area(char **area, int n)
{
	int	i;

	if (!area)
		return ;
	i = 0;
	while (i < n)
	{
		free(area[i]);
		i++;
	}
	free(area);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->area)
	{
		i = 0;
		while (map->area[i])
		{
			free(map->area[i]);
			map->area[i] = NULL;
			i++;
		}
		free(map->area);
	}
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	free(map);
}
