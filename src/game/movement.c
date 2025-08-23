#include "cub3D.h"

#define MOVE_SPEED 5
#define ROTATION_SPEED 3.0
#define COLLISION_BUFFER 5
#define TILE_SIZE 64

// /* Check if position is valid (not a wall) */
// // static int can_move_to(t_map *map, double x, double y)
// // {
// // 	int map_x = (int)x;
// // 	int map_y = (int)y;
	
// // 	if (map_y < 0 || map_y >= map->size_y)
// // 		return (0);
// // 	if (!map->area[map_y])
// // 		return (0);
// // 	if (map_x < 0 || map_x >= (int)ft_strlen(map->area[map_y]))
// // 		return (0);
// // 	if (map->area[map_y][map_x] == '1' || map->area[map_y][map_x] == ' ')
// // 		return (0);
// // 	return (1);
// // }
// /* Check if position is valid (not colliding with walls, with buffer) */
// // /* Check if position is valid (with circular collision buffer against wall squares) */

// /* Simpler collision check */
// static int collides(t_map *map, double x, double y)
// {
//     int min_x = (int)floor(x - COLLISION_BUFFER);
//     int max_x = (int)floor(x + COLLISION_BUFFER);
//     int min_y = (int)floor(y - COLLISION_BUFFER);
//     int max_y = (int)floor(y + COLLISION_BUFFER);

//     for (int yy = min_y; yy <= max_y; yy++)
//     {
//         for (int xx = min_x; xx <= max_x; xx++)
//         {
//             if (yy < 0 || yy >= map->size_y)
//                 return (1);
//             if (!map->area[yy])
//                 return (1);
//             if (xx < 0 || xx >= (int)ft_strlen(map->area[yy]))
//                 return (1);

//             char tile = map->area[yy][xx];
//             if (tile == '1' || tile == ' ')
//             {
//                 // Clamp player position to edge of square
//                 double closest_x = fmax(xx, fmin(x, xx + 1));
//                 double closest_y = fmax(yy, fmin(y, yy + 1));

//                 double dx = x - closest_x;
//                 double dy = y - closest_y;
//                 double dist_sq = dx * dx + dy * dy;

//                 if (dist_sq < (COLLISION_BUFFER * COLLISION_BUFFER))
//                 {
//                     printf("Blocked by tile '%c' at (%d, %d)\n", tile, xx, yy);
//                     return (1);
//                 }
//             }
//         }
//     }
//     return (0);
// }




// /* safe movement */
// void try_move(t_map *map, double *px, double *py, double dx, double dy)
// {
//     double new_x = *px + dx;
//     double new_y = *py + dy;

//     // Debug prints
//     printf("Current pos: (%.2f, %.2f)\n", *px, *py);
//     printf("Trying to move to: (%.2f, %.2f)\n", new_x, new_y);
    
//     // Check X first
//     if (!collides(map, new_x, *py))
//     {
//         *px = new_x;
//         printf("X movement allowed\n");
//     }
//     else
//         printf("X movement blocked\n");

//     // Then Y
//     if (!collides(map, *px, new_y))
//     {
//         *py = new_y;
//         printf("Y movement allowed\n");
//     }
//     else
//         printf("Y movement blocked\n");
// }





// /* Move player forward/backward */
// // void move_forward_backward(t_game *game, int forward)
// // {
// // 	double angle_rad;
// // 	double dx;
// // 	double dy;
// // 	double new_x;
// // 	double new_y;
// // 	double speed;

// // 	if (forward)
// // 		speed = MOVE_SPEED;
// // 	else
// // 		speed = -MOVE_SPEED;
// // 	angle_rad = game->map->hero.angle * M_PI / 180.0;
	
// // 	dx = sin(angle_rad) * speed;
// // 	dy = -cos(angle_rad) * speed;
	
// // 	new_x = game->map->hero.x + dx;
// // 	new_y = game->map->hero.y + dy;
	
// // 	if (can_move_to(game->map, new_x, game->map->hero.y))
// // 		game->map->hero.x = new_x;
// // 	if (can_move_to(game->map, game->map->hero.x, new_y))
// // 		game->map->hero.y = new_y;
// // }

// // /* Strafe left/right */
// // void move_left_right(t_game *game, int left)
// // {
// // 	double angle_rad;
// // 	double dx;
// // 	double dy;
// // 	double new_x;
// // 	double new_y;
// // 	double speed;

// // 	if (left)
// // 		speed = -MOVE_SPEED;
// // 	else
// // 		speed = MOVE_SPEED;
// // 	angle_rad = game->map->hero.angle * M_PI / 180.0;  // Perpendicular angle
	
// // 	dx = cos(angle_rad) * speed;
// // 	dy = sin(angle_rad) * speed;

// // 	new_x = game->map->hero.x + dx;
// // 	new_y = game->map->hero.y + dy;
	
// // 	if (can_move_to(game->map, new_x, game->map->hero.y))
// // 		game->map->hero.x = new_x;
// // 	if (can_move_to(game->map, game->map->hero.x, new_y))
// // 		game->map->hero.y = new_y;
// // }
// void move_forward_backward(t_game *game, int forward)
// {
//     double angle_rad = game->map->hero.angle * M_PI / 180.0;
//     double speed = forward ? MOVE_SPEED : -MOVE_SPEED;

//     double dx = sin(angle_rad) * speed;
//     double dy = -cos(angle_rad) * speed;

//     try_move(game->map, &game->map->hero.x, &game->map->hero.y, dx, dy);
// }
// void move_left_right(t_game *game, int left)
// {
//     double angle_rad = game->map->hero.angle * M_PI / 180.0;
//     double speed = left ? -MOVE_SPEED : MOVE_SPEED;

//     double dx = cos(angle_rad) * speed;
//     double dy = sin(angle_rad) * speed;

//     try_move(game->map, &game->map->hero.x, &game->map->hero.y, dx, dy);
// }


// /* Rotate player left/right */
// void rotate_player(t_game *game, int left)
// {
// 	double rotation;
	
// 	if (left)
// 		rotation = -ROTATION_SPEED;
// 	else
// 		rotation = ROTATION_SPEED;
// 	game->map->hero.angle += rotation;
	
// 	// Keep angle in 0-360 range
// 	if (game->map->hero.angle < 0)
// 		game->map->hero.angle += 360;
// 	if (game->map->hero.angle >= 360)
// 		game->map->hero.angle -= 360;
// }

// /* Handle all movement input */
// void handle_movement(t_game *game)
// {
// 	// Forward/Backward movement
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
// 		move_forward_backward(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
// 		move_forward_backward(game, 0);
	
// 	// Left/right movement
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
// 		move_left_right(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
// 		move_left_right(game, 0);
	
// 	// Rotation
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 		rotate_player(game, 1);
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 		rotate_player(game, 0);
// }
int check_collision(t_game *game, double new_x, double new_y)
{
	int tile_x, tile_y;

	// Top-left
	tile_x = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1' || game->map->area[tile_y][tile_x] == ' ')
		return (0);

	// Top-right
	tile_x = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y - COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1' || game->map->area[tile_y][tile_x] == ' ')
		return (0);

	// Bottom-left
	tile_x = (int)((new_x - COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1' || game->map->area[tile_y][tile_x] == ' ')
		return (0);

	// Bottom-right
	tile_x = (int)((new_x + COLLISION_BUFFER) / TILE_SIZE);
	tile_y = (int)((new_y + COLLISION_BUFFER) / TILE_SIZE);
	if (game->map->area[tile_y][tile_x] == '1' || game->map->area[tile_y][tile_x] == ' ')
		return (0);

	return (1); // Movement is allowed
}

/* Apply movement with collision */
void try_move(t_game *game, double dx, double dy)
{
	double new_x = game->map->hero.x + dx;
	double new_y = game->map->hero.y + dy;
	// printf("Current position: %.2f, %.2f\n", game->map->hero.x, game->map->hero.y);
	// printf("Trying move: dx=%.2f dy=%.2f -> new_x=%.2f new_y=%.2f\n",dx, dy, new_x, new_y);
	if (check_collision(game, new_x, game->map->hero.y))
		game->map->hero.x = new_x;
	if (check_collision(game, game->map->hero.x, new_y))
		game->map->hero.y = new_y;
	// if (!check_collision(game, new_x, game->map->hero.y))
	// 	printf("Blocked in X\n");

	// if (!check_collision(game, game->map->hero.x, new_y))
	// 	printf("Blocked in Y\n");
}

/* Move player forward/backward */
void move_forward_backward(t_game *game, int forward)
{
	double angle_rad;
	double speed;

	angle_rad = game->map->hero.angle * M_PI / 180.0;
	if (forward)
		speed = MOVE_SPEED;
	else
		speed = -MOVE_SPEED;
	double dx = sin(angle_rad) * speed;
	double dy = -cos(angle_rad) * speed;

	try_move(game, dx, dy);
}

/* Strafe left/right */
void move_left_right(t_game *game, int left)
{
	double angle_rad;
	double speed;

	angle_rad = game->map->hero.angle * M_PI / 180.0;
	if (left)
		speed = -MOVE_SPEED;
	else
		speed = MOVE_SPEED;
	double dx = cos(angle_rad) * speed;
	double dy = sin(angle_rad) * speed;

	try_move(game, dx, dy);
}

/* Rotate player */
void rotate_player(t_game *game, int left)
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
void handle_movement(t_game *game)
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