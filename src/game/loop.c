#include "cub3D.h"

void	close_game(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (game->tx.tex[i])
			mlx_delete_texture(game->tx.tex[i]);
		i++;
	}
}

void key_press(mlx_key_data_t keydata, void* param)
{
	t_game *game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

void	cleanup_and_exit(void *param)
{
	t_game *game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}

void game_update(void *param)
{
    t_game *game;
	
	game = (t_game *)param;
	handle_movement(game);
    ft_memset(game->img->pixels, 0, game->img->width * game->img->height \
		* sizeof(uint32_t));
    
    draw_background(game);
    render_view(game);
}

void game_loop(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!game->mlx)
		return (err_msg("Failed to initialize MLX"));

	setup_input(game);

	if (load_all_textures(game) < 0)
		return (mlx_terminate(game->mlx));

	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		return (err_msg("Failed to create image"));
	}
	draw_background(game);
	render_view(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	//mlx_image_to_window(game->mlx, game->wand,  WINDOW_WIDTH - WAND_W - 10,
	mlx_image_to_window(game->mlx, game->wand, 400, 500);


	// Register a hook for any key press
	mlx_key_hook(game->mlx, &key_press, game);
	
	// Register a hook for when the user clicks the close button on the window
	
	// Регистрируем хуки
	mlx_loop_hook(game->mlx, &game_update, game);
	mlx_close_hook(game->mlx, &cleanup_and_exit, game);

	// Запускаем цикл обработки событий MLX
	mlx_loop(game->mlx);
	
	// Эта часть кода выполняется ПОСЛЕ завершения mlx_loop
	close_game(game);         // Сначала освобождаем ресурсы игры
	mlx_terminate(game->mlx); // В самом конце завершаем работу MLX
}
