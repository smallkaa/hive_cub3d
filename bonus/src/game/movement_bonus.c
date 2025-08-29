/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvershin <pvershin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:29:37 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/08/29 12:55:48 by pvershin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

/*
** @brief  Attempt to move player with collision check.
** @details Applies dx/dy offsets, updates position only if
**          check_collision() allows movement.
*/
void	try_move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->map->hero.x + dx;
	new_y = game->map->hero.y + dy;
	if (check_collision(game, new_x, game->map->hero.y))
		game->map->hero.x = new_x;
	if (check_collision(game, game->map->hero.x, new_y))
		game->map->hero.y = new_y;
}

/*
** @brief  Move player forward or backward.
** @details Uses hero angle and MOVE_SPEED to compute dx/dy.
** @param   forward 1 = forward, 0 = backward.
*/
void	move_forward_backward(t_game *game, int forward)
{
	double	angle_rad;
	double	speed;
	double	dx;
	double	dy;

	angle_rad = game->map->hero.angle * M_PI / 180.0;
	if (forward)
		speed = MOVE_SPEED;
	else
		speed = -MOVE_SPEED;
	dx = sin(angle_rad) * speed;
	dy = -cos(angle_rad) * speed;
	try_move(game, dx, dy);
}

/*
** @brief  Strafe player left or right.
** @details Computes perpendicular movement using hero angle.
** @param   left 1 = left, 0 = right.
*/
void	move_left_right(t_game *game, int left)
{
	double	angle_rad;
	double	speed;
	double	dx;
	double	dy;

	angle_rad = game->map->hero.angle * M_PI / 180.0;
	if (left)
		speed = -MOVE_SPEED;
	else
		speed = MOVE_SPEED;
	dx = cos(angle_rad) * speed;
	dy = sin(angle_rad) * speed;
	try_move(game, dx, dy);
}

/*
** @brief  Rotate player left or right.
** @details Adjusts hero angle by ROTATION_SPEED, keeps value in [0,360).
** @param   left 1 = rotate left, 0 = rotate right.
*/
void	rotate_player(t_game *game, int left)
{
	if (left)
		game->map->hero.angle -= ROTATION_SPEED;
	else
		game->map->hero.angle += ROTATION_SPEED;
	if (game->map->hero.angle < 0)
		game->map->hero.angle += 360;
	if (game->map->hero.angle >= 360)
		game->map->hero.angle -= 360;
}

/*
** @brief  Handle all movement inputs.
** @details Reads WASD for movement and arrow keys for rotation,
**          dispatches to movement/rotation helpers.
*/
void	handle_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward_backward(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward_backward(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left_right(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left_right(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, 1);
}
