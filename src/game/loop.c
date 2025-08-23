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
    if (game->minimap)
    {
        printf("Cleaning up minimap image\n");
        // Don't delete the image - MLX will handle it
        game->minimap = NULL;
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
	if (!game || !game->img)
        return;
	handle_movement(game);
    ft_memset(game->img->pixels, 0, game->img->width * game->img->height \
		* sizeof(uint32_t));
    
    draw_background(game);
    render_view(game);

	printf("Updating minimap...\n");  // Debug line
    draw_minimap(game);
}

// void game_loop(t_game *game)
// {
// 	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
// 	if (!game->mlx)
// 		return (err_msg("Failed to initialize MLX"));

// 	setup_input(game);

// 	if (load_all_textures(game) < 0)
// 		return (mlx_terminate(game->mlx));

// 	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// 	if (!game->img)
// 	{
// 		mlx_terminate(game->mlx);
// 		return (err_msg("Failed to create image"));
// 	}
// 	draw_background(game);
// 	render_view(game);
// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// 	//mlx_image_to_window(game->mlx, game->wand,  WINDOW_WIDTH - WAND_W - 10,
// 	if (minimap_init(game, &game->minimap) < 0)
// 	{
//     	mlx_terminate(game->mlx);
//     	return (err_msg("minimap init failed"));
// 	}
// 	mlx_image_to_window(game->mlx, game->wand, 400, 650);


// 	// Register a hook for any key press
// 	mlx_key_hook(game->mlx, &key_press, game);
	
// 	// Register a hook for when the user clicks the close button on the window
	
// 	// Регистрируем хуки
// 	mlx_loop_hook(game->mlx, &game_update, game);
// 	mlx_close_hook(game->mlx, &cleanup_and_exit, game);

// 	// Запускаем цикл обработки событий MLX
// 	mlx_loop(game->mlx);
	
// 	// Эта часть кода выполняется ПОСЛЕ завершения mlx_loop
// 	close_game(game);         // Сначала освобождаем ресурсы игры
// 	mlx_terminate(game->mlx); // В самом конце завершаем работу MLX
// }
void game_loop(t_game *game)
{
    game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
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
    
    // ✅ ENABLE MAIN IMAGE (this is safe)
    game->img->enabled = true;
    printf("Main image enabled\n");
    
    // if (minimap_init(game) < 0)
    // {
    //     mlx_terminate(game->mlx);
    //     return (err_msg("minimap init failed"));
    // }
    mlx_image_to_window(game->mlx, game->wand, 400, 650);
    game->minimap = mlx_new_image(game->mlx, MINIMAP_MARGIN * 2 + game->map->size_x * MINIMAP_TILE, MINIMAP_MARGIN * 2 + game->map->size_y * MINIMAP_TILE);

    mlx_image_to_window(game->mlx, game->minimap, 0, 0);
    //mlx_image_to_window(game->mlx, game->minimap, 100, 700);
    
    
    // ✅ ENABLE WAND IMAGE
    game->wand->enabled = true;
    printf("Wand image enabled\n");
    
    // Register hooks
    mlx_key_hook(game->mlx, &key_press, game);
    //mlx_loop_hook(game->mlx, &minimap_draw, game);
    mlx_loop_hook(game->mlx, &game_update, game);
 
    
    mlx_close_hook(game->mlx, &cleanup_and_exit, game);

    mlx_loop(game->mlx);
    
    close_game(game);
    mlx_terminate(game->mlx);
}