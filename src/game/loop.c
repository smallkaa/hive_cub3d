#include "cub3D.h"

// This function will be called to free memory and exit the game
void	close_game(t_game *game)
{
	int i = 0;

	while (i < 4)
	{
		if (game->tx.tex[i])
		{
			mlx_delete_texture(game->tx.tex[i]);
		}
		i++;
	}
// Terminate MLX and exit
	mlx_terminate(game->mlx);
}

// This function will be called when a key is pressed
void key_press(mlx_key_data_t keydata, void* param)
{
	t_game *game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(game);
}

// This is for the window's close button
void	cleanup_and_exit(void *param)
{
	t_game *game = (t_game *)param;
	close_game(game);
}
void game_update(void *param)
{
	t_game *game = (t_game *)param;

	handle_movement(game);
	
	// Clear the image
	ft_memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(uint32_t));
	
	// Redraw everything
	draw_background(game);
	render_view(game);
}
void game_loop(t_game *game)
{
	// Initialize MLX42 and create a window
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!game->mlx)
	{
		err_msg("Failed to initialize MLX");
		return ;
	}
	setup_input(game);

	if (load_all_textures(game) < 0)
	{
		mlx_terminate(game->mlx);
		return;
	}
	// Create a new image to draw on
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		err_msg("Failed to create image");
		return ;
	}
	
	
	// Draw the background colors to the image
	draw_background(game);
	render_view(game);
	// Place the image onto the window
	mlx_image_to_window(game->mlx, game->img, 0, 0);

	// Register a hook for any key press
	mlx_key_hook(game->mlx, &key_press, game);
	
	// Register a hook for when the user clicks the close button on the window
	mlx_loop_hook(game->mlx, &game_update, game);
	mlx_close_hook(game->mlx, &cleanup_and_exit, game);

	// Start the MLX event loop
	mlx_loop(game->mlx);
	
	// This part is reached after the loop ends
	mlx_terminate(game->mlx);
}