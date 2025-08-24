#include "cub3D.h"

/* Apply movement with collision */
void	try_move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->map->hero.x + dx;
	new_y = game->map->hero.y + dy;
	// printf("Current position: %.2f, %.2f\n", game->map->hero.x, game->map->hero.y);
	// printf("Trying move: dx=%.2f dy=%.2f -> new_x=%.2f new_y=%.2f\n",dx, dy,new_x, new_y);
	if (check_collision(game, new_x, game->map->hero.y))
		game->map->hero.x = new_x;
	if (check_collision(game, game->map->hero.x, new_y))
		game->map->hero.y = new_y;
}

/* Move player forward/backward */
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

/* Strafe left/right */
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

/* Rotate player */
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

/* Handle movement input */
void	handle_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward_backward(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward_backward(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left_right(game, 1); // D = right
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left_right(game, 0); // A = left
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, 1);
}
