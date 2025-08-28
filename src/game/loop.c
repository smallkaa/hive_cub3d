/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:27:59 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/28 12:47:24 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

void	cleanup_and_exit(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}

void	game_update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_movement(game);
	ft_memset(game->img->pixels, 0, game->img->width * game->img->height
		* sizeof(uint32_t));
	draw_background(game);
	render_view(game);
}

int	game_loop(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game->mlx) // no  leaks
		return (err_msg("Failed to initialize MLX"), -1);
	if (load_all_textures(game) < 0)
		return (mlx_terminate(game->mlx), -1);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		free_resources(game);
		return (mlx_terminate(game->mlx), err_msg("Failed to create img"), -1);
	}
	draw_background(game);
	render_view(game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		return (free_resources(game), err_msg("mlx function has failed"), 1);
	if (mlx_image_to_window(game->mlx, game->wand, 400, 650) == -1)
		return (free_resources(game), err_msg("mlx function has failed"), -1);
	mlx_key_hook(game->mlx, &key_press, game);
	mlx_loop_hook(game->mlx, &game_update, game);
	mlx_close_hook(game->mlx, &cleanup_and_exit, game);
	mlx_loop(game->mlx);
	close_game(game);
	mlx_terminate(game->mlx);
	return (0);
}
