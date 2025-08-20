/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: you                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:40:00 by you               #+#    #+#             */
/*   Updated: 2025/08/20 18:40:00 by you              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Return 1 if (Q with SUPER) or (Q with CONTROL), else 0 */
static int	is_quit_combo(mlx_key_data_t k)
{
	if (k.key == MLX_KEY_Q && (k.modifier & MLX_SUPERKEY))
		return (1);
	if (k.key == MLX_KEY_Q && (k.modifier & MLX_CONTROL))
		return (1);
	return (0);
}

/* Close on ESC, plain 'q', Command+Q (mac), Ctrl+Q (linux). */
static void	on_key(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_Q && keydata.modifier == 0)
		mlx_close_window(game->mlx);
	else if (is_quit_combo(keydata))
		mlx_close_window(game->mlx);
}

/* Public: register the key hook. */
void	setup_input(t_game *game)
{
	mlx_key_hook(game->mlx, &on_key, game);
}
