#include "cub3D.h"

#define MOVE_SPEED 0.03
#define ROTATION_SPEED 3.0

/* Check if position is valid (not a wall) */
static int can_move_to(t_map *map, double x, double y)
{
	int map_x = (int)x;
	int map_y = (int)y;
	
	if (map_y < 0 || map_y >= map->size_y)
		return (0);
	if (!map->area[map_y])
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(map->area[map_y]))
		return (0);
	if (map->area[map_y][map_x] == '1' || map->area[map_y][map_x] == ' ')
		return (0);
	return (1);
}

/* Move player forward/backward */
void move_forward_backward(t_game *game, int forward)
{
	double angle_rad;
	double dx;
	double dy;
	double new_x;
	double new_y;
	double speed;

	if (forward)
		speed = MOVE_SPEED;
	else
		speed = -MOVE_SPEED;
	angle_rad = game->map->hero.angle * M_PI / 180.0;
	
	dx = sin(angle_rad) * speed;
	dy = -cos(angle_rad) * speed;
	
	new_x = game->map->hero.x + dx;
	new_y = game->map->hero.y + dy;
	
	if (can_move_to(game->map, new_x, game->map->hero.y))
		game->map->hero.x = new_x;
	if (can_move_to(game->map, game->map->hero.x, new_y))
		game->map->hero.y = new_y;
}

/* Strafe left/right */
void move_left_right(t_game *game, int left)
{
	double angle_rad;
	double dx;
	double dy;
	double new_x;
	double new_y;
	double speed;

	if (left)
		speed = -MOVE_SPEED;
	else
		speed = MOVE_SPEED;
	angle_rad = game->map->hero.angle * M_PI / 180.0;  // Perpendicular angle
	
	dx = cos(angle_rad) * speed;
	dy = sin(angle_rad) * speed;

	new_x = game->map->hero.x + dx;
	new_y = game->map->hero.y + dy;
	
	if (can_move_to(game->map, new_x, game->map->hero.y))
		game->map->hero.x = new_x;
	if (can_move_to(game->map, game->map->hero.x, new_y))
		game->map->hero.y = new_y;
}

/* Rotate player left/right */
void rotate_player(t_game *game, int left)
{
	double rotation;
	
	if (left)
		rotation = -ROTATION_SPEED;
	else
		rotation = ROTATION_SPEED;
	game->map->hero.angle += rotation;
	
	// Keep angle in 0-360 range
	if (game->map->hero.angle < 0)
		game->map->hero.angle += 360;
	if (game->map->hero.angle >= 360)
		game->map->hero.angle -= 360;
}

/* Handle all movement input */
void handle_movement(t_game *game)
{
	// Forward/Backward movement
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward_backward(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_forward_backward(game, 0);
	
	// Left/right movement
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left_right(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left_right(game, 0);
	
	// Rotation
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, 0);
}
