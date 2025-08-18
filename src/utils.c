#include "cub3D.h"

void	err_msg(char *msg)
{
	int	len;

	len = 0;
	if (!msg)
		return ;
	while (msg[len] != '\0')
		len++;
	write(2, "Error : ", 8);
	write(2, msg, len);
	write(2, "\n", 1);
}
// void	error_msg(char *msg)
// {
// 	ft_putendl_fd(msg, 2);
// }

void free_map(t_map *map)
{
	int i;

	if (!map || !map->area)
		return;
	i = 0;
	while (map->area[i])
	{
		free(map->area[i]);
		i++;
	}
	free(map->area);
	map->area = NULL;
	map->size_y = 0;
}