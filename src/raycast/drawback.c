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