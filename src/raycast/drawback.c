#include "cub3D.h"

// This function draws the ceiling and floor
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->ceil_c);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->img, x, y, game->map->floor_c);
			x++;
		}
		y++;
	}
}

/*
** @brief      Checks if a given coordinate (x, y) on the map is a wall.
** @details    1. Verifies if the y-coordinate is within the map's height.
** 2. Verifies if the x-coordinate is within the width of the
** corresponding row.
** 3. Returns 1 (true) if the coordinate is out of bounds or if the
** character at that position is '1' (a wall) or ' ' (empty
** space, also treated as a wall).
** 4. Returns 0 (false) otherwise.
*/
int	map_is_wall(t_map *m, int x, int y)
{
	size_t	len;

	if (y < 0 || y >= m->size_y || !m->area[y])
		return (1);
	len = ft_strlen(m->area[y]);
	if (x < 0 || (size_t)x >= len)
		return (1);
	if (m->area[y][x] == '1' || m->area[y][x] == ' ')
		return (1);
	return (0);
}
