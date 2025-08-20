#include "cub3D.h"
//#include "MLX42/MLX42.h" // Make sure this is the correct path
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h> // For exit()

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Forward declaration
void	cleanup_and_exit(void *param);

// This function will be called to free memory and exit the game
void	close_game(t_game *game)
{
	// free your map struct here
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	// Terminate MLX and exit
	mlx_terminate(game->mlx);
	exit(0);
}

// This function will be called when a key is pressed
void key_press(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;
	(void)keydata; // Unused parameter
	
	close_game(game);
}


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

// This is for the window's close button
void	cleanup_and_exit(void *param)
{
	t_game *game = (t_game *)param;
	close_game(game);
}


int	main(int ac, char **av)
{
	t_map *map;
	
	t_game game;

	printf("Starting parsing...\n");
	if (ac != 2)
	{
		return (err_msg("Usage: ./cub3d <file.cub>"), 1);
	}
	map = parsing_args(av[1]);
	 if (!map)
		return (1);
	printf("NO: %s\n", map->no);
	printf("SO: %s\n", map->so);
	printf("WE: %s\n", map->we);
	printf("EA: %s\n", map->ea);
	printf("Floor color: %u\n", map->floor_c);
	printf("Ceil color: %u\n", map->ceil_c);
	printf("map size %d\n", map->size_y);
	printf("Player position x- %f y - %f\n, angle - %f\n", map->hero.x, map->hero.y, map->hero.angle);
	for(int i = 0; map->area[i]; i++)
		printf("%s\n", map->area[i]);

	// Initialize MLX42 and create a window
	game.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!game.mlx)
	{
		err_msg("Failed to initialize MLX");
		free_map(map);
		return (1);
	}

	// Create a new image to draw on
	game.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game.img)
	{
		mlx_terminate(game.mlx);
		err_msg("Failed to create image");
		free_map(map);
		return (1);
	}
	
	game.map = map;
	
	// Draw the background colors to the image
	draw_background(&game);
	
	// Place the image onto the window
	mlx_image_to_window(game.mlx, game.img, 0, 0);

	// Register a hook for any key press
	mlx_key_hook(game.mlx, &key_press, &game);
	
	// Register a hook for when the user clicks the close button on the window
	mlx_close_hook(game.mlx, &cleanup_and_exit, &game);

	// Start the MLX event loop
	mlx_loop(game.mlx);
	
	// This part is reached after the loop ends
	mlx_terminate(game.mlx);
	free_map(map);
	return (0);
}
