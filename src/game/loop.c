#include "cub3D.h"

// Эта функция теперь только освобождает ресурсы игры (текстуры).
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
	// УБИРАЕМ mlx_terminate ОТСЮДА. ЭТО ГЛАВНАЯ ПРИЧИНА ПАДЕНИЯ.
}

// Эта функция будет вызвана при нажатии клавиши (сейчас не используется)
void key_press(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	
	game = (t_game *)param;
	(void)keydata;
	// Правильное действие для выхода по клавише - также закрыть окно.
	mlx_close_window(game->mlx);
}

// Эта функция теперь правильно обрабатывает закрытие окна.
void	cleanup_and_exit(void *param)
{
	t_game *game;

	game = (t_game *)param;
	// Просто даём сигнал mlx_loop, что нужно завершиться.
	mlx_close_window(game->mlx);
}

void game_update(void *param)
{
    t_game *game;
	
	game = (t_game *)param;
    // Очищаем изображение
    ft_memset(game->img->pixels, 0, game->img->width * game->img->height \
		* sizeof(uint32_t));
    
    // Перерисовываем всё
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
	
	// Регистрируем хуки
	mlx_loop_hook(game->mlx, &game_update, game);
	mlx_close_hook(game->mlx, &cleanup_and_exit, game);

	// Запускаем цикл обработки событий MLX
	mlx_loop(game->mlx);
	
	// Эта часть кода выполняется ПОСЛЕ завершения mlx_loop
	close_game(game);         // Сначала освобождаем ресурсы игры
	mlx_terminate(game->mlx); // В самом конце завершаем работу MLX
}