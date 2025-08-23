#include "cub3D.h"

// // Safe pixel putting function with bounds checking
// // static void mm_put(mlx_image_t *img, int x, int y, uint32_t color)
// // {
// //     if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
// //         mlx_put_pixel(img, x, y, color);
// // }



// static void get_tile(t_game *game, t_mini *mini)
// {
//     float rotation_angle;

//     rotation_angle = game->map->hero.angle * M_PI / 180.0f - NORTH_POV;

//     mini->rdx = mini->dx * cosf(rotation_angle) - mini->dy * sinf(rotation_angle);
//     mini->rdy = mini->dx * sinf(rotation_angle) + mini->dy * cosf(rotation_angle);

// }
// void    put_pixel_mini(t_game *game, t_mini *mini)
// {
//     uint32_t    color;
//     int            x;
//     int            y;

//     x = MINIMAP_RADIUS + mini->dx;
//     y = MINIMAP_RADIUS + mini->dy;
//     color = 0xAAAAAA00;
//     // if (mini.tile_y < game->size_x && mini.tile_x
//     //     < (int)ft_strlen(game->map[mini.tile_y]))
//     if (!(mini->tile_y < 0 || mini->tile_y >= game->map->size_y || 
//         mini->tile_x < 0 || mini->tile_x >= (int)ft_strlen(game->map->area[mini->tile_y])))
// //     {
//     {
//         char cell = game->map->area[mini->tile_y][mini->tile_x];
//         if (game->map->area[mini->tile_y][mini->tile_x] == '1')
//             color = 0x444444FF;
//         else if ((cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W'))
//             color = 0xAAAAAAFF;
//         else
//             return ;
//     }
//     mlx_put_pixel(game->minimap, x, y, color);
// }
// //static void put_pixel_mini(t_game *game, t_mini *mini)
// // {
// //     uint32_t color;
// //     int screen_x, screen_y;
    
// //     if (mini->tile_y < 0 || mini->tile_y >= game->map->size_y || 
// //         mini->tile_x < 0 || mini->tile_x >= (int)ft_strlen(game->map->area[mini->tile_y]))
// //     {
// //         color = MM_ALPHA(255, 100, 100, 100);  // Gray - more visible
// //     }
// //     else
// //     {
// //         char cell = game->map->area[mini->tile_y][mini->tile_x];
// //         if (cell == '1')
// //             color = MM_ALPHA(255, 255, 255, 255);  // ✅ WHITE walls - very visible
// //         else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
// //             color = MM_ALPHA(255, 0, 255, 0);      // ✅ GREEN floor - very visible
// //         else
// //             color = MM_ALPHA(255, 100, 100, 100);
// //     }
    
// //     screen_x = (int)mini->dx + MINIMAP_RADIUS;
// //     screen_y = (int)mini->dy + MINIMAP_RADIUS;
// //     mlx_put_pixel(game->minimap, screen_x, screen_y, color);
// //     // mm_put(game->minimap, screen_x, screen_y, color);
// // }

// // static void put_dot(mlx_image_t *img, int x, int y, uint32_t color)
// // {
// //     for (int dy = -1; dy <= 1; dy++)
// //         for (int dx = -1; dx <= 1; dx++)
// //             mm_put(img, x + dx, y + dy, color);
// // }

// static void clean_minimap(t_game *game)
// {
//     // ✅ Use BRIGHT RED background for debugging
//     //uint32_t bg_color = MM_ALPHA(255, 255, 0, 0);  // Bright red
// 	uint32_t bg_color = MM_ALPHA(255, 100, 100, 100);//0xFF000000; 
    
//     // printf("Cleaning minimap - size: %dx%d\n", 
//     //        (int)game->minimap->width, (int)game->minimap->height);
    
//     for (int y = 0; y < (int)game->minimap->height; y++)
//         for (int x = 0; x < (int)game->minimap->width; x++)
//             mlx_put_pixel(game->minimap, x, y, bg_color);
// }

// static void put_minimap(t_game *game)
// {
//     t_mini mini;


//     ft_memset(&mini, 0, sizeof(t_mini));
//    // mini.dx = -MINIMAP_RADIUS;
//     mini.dy = -MINIMAP_RADIUS; 

   
    
    
//     while (mini.dy < MINIMAP_RADIUS)
//     {
//         mini.dx = -MINIMAP_RADIUS;
//         while (mini.dx < MINIMAP_RADIUS)
//         {
//             if (mini.dx * mini.dx + mini.dy * mini.dy > MINIMAP_RADIUS * MINIMAP_RADIUS)
//             {
//                 mini.dx++;
//                 continue;
//             }
            
//             get_tile(game, &mini);
            
//             if (mini.tile_y >= 0 && mini.tile_y < game->map->size_y &&
//                 mini.tile_x >= 0 && mini.tile_x < game->map->size_x)
//             {
//                 put_pixel_mini(game, &mini);

//             }
//             mini.dx++;
//         }
//         mini.dy++;
//     }
// }

// void minimap_draw(void *param)
// {
//     t_game *g;
//     g = (t_game *)param;
//     clean_minimap(g);
//     put_minimap(g);
//     //put_dot(g->minimap, MINIMAP_RADIUS, MINIMAP_RADIUS, MM_ALPHA(255, 0, 255, 0));
    
//     // float angle = g->map->hero.angle * M_PI / 180.0;
//     // int dir_x = MINIMAP_RADIUS + (int)(cos(angle - M_PI_2) * 15);
//     // int dir_y = MINIMAP_RADIUS + (int)(sin(angle - M_PI_2) * 15);
    
//     // int steps = 15;
//     // for (int i = 0; i <= steps; i++)
//     // {
//     //     int x = MINIMAP_RADIUS + (i * (dir_x - MINIMAP_RADIUS)) / steps;
//     //     int y = MINIMAP_RADIUS + (i * (dir_y - MINIMAP_RADIUS)) / steps;
//     //     mm_put(g->minimap, x, y, MM_ALPHA(255, 255, 255, 0));
//     // }
// 	printf("Drawing SIMPLE test minimap...\n");
 
// }
// // void minimap_draw(t_game *g)
// // {
// //     printf("Drawing VISIBLE test minimap...\n");
// //     // Fill entire minimap with BRIGHT SOLID COLORS
// //     for (int y = 0; y < (int)g->minimap->height; y++)
// //     {
// //         for (int x = 0; x < (int)g->minimap->width; x++)
// //         {
// //             uint32_t color;
            
// //             // Create a very visible pattern
// //             if (x < 5 || x >= (int)g->minimap->width - 5 || 
// //                 y < 5 || y >= (int)g->minimap->height - 5)
// //             {
// //                 // Thick red border
// //                 color = 0xFF0000FF;  // SOLID RED
// //             }
// //             else if ((x / 10 + y / 10) % 2 == 0)
// //             {
// //                 // White checkerboard
// //                 color = 0xFFFFFFFF;  // SOLID WHITE
// //             }
// //             else
// //             {
// //                 // Blue checkerboard
// //                 color = 0xFF0000FF;  // SOLID BLUE (wait, this should be different)
// //                 color = 0x0000FFFF;  // SOLID BLUE
// //             }
            
// //             mlx_put_pixel(g->minimap, x, y, color);
// //         }
// //     }
    
// //     // Draw a big yellow center dot (player position)
// //     for (int dy = -10; dy <= 10; dy++)
// //     {
// //         for (int dx = -10; dx <= 10; dx++)
// //         {
// //             if (dx * dx + dy * dy <= 100)  // Circle
// //             {
// //                 int px = g->minimap->width / 2 + dx;
// //                 int py = g->minimap->height / 2 + dy;
// //                 if (px >= 0 && px < (int)g->minimap->width && 
// //                     py >= 0 && py < (int)g->minimap->height)
// //                     mlx_put_pixel(g->minimap, px, py, 0xFFFF00FF);  // SOLID YELLOW
// //             }
// //         }
// //     }
    
// //     printf("Highly visible test pattern drawn!\n");
// // }

// int minimap_init(t_game *g)
// {
//     int diameter = MINIMAP_RADIUS * 2;
    
//     g->minimap = mlx_new_image(g->mlx, diameter, diameter);
//     if (!g->minimap)
//     {
//         printf("ERROR: Failed to create minimap image!\n");
//         return (-1);
//     }
//     printf("Minimap image created: %dx%d\n", diameter, diameter);

//     if (mlx_image_to_window(g->mlx, g->minimap, 20, 20) < 0)
//     {
//         printf("ERROR: Failed to add minimap to window!\n");
//         return (-1);
//     }
//     printf("Minimap added to window at (20, 20)\n");

//     g->minimap->instances[0].z = 1000;  // Reduce Z value
//     g->minimap->enabled = true;
//     printf("Minimap enabled with Z=%d\n", g->minimap->instances[0].z);
    
//     return (0);
// }
void clear_minimap(mlx_image_t *img, uint32_t color)
{
	for (uint32_t y = 0; y < img->height; y++)
		for (uint32_t x = 0; x < img->width; x++)
			mlx_put_pixel(img, x, y, color);
}

void draw_minimap(t_game *game)
{
	if (!game || !game->map || !game->map->area || !game->minimap)
		return;

	mlx_image_t *img = game->minimap;
	clear_minimap(img, 0x00FFCCFF); // заливаем чёрным фоном

	for (int y = 0; y < game->map->size_y; y++)
	{
		for (int x = 0; x < game->map->size_x; x++)
		{
			char c = game->map->area[y][x];
			uint32_t color;

			if (c == '1')
				color = 0x006666FF; // стены
			else if (c == '0' || c == ' ')
				color = 0x222222FF; // пол
			else
				continue;

			for (int dy = 0; dy < MINIMAP_TILE; dy++)
			{
				for (int dx = 0; dx < MINIMAP_TILE; dx++)
				{
					int px = MINIMAP_MARGIN + x * MINIMAP_TILE + dx;
					int py = MINIMAP_MARGIN + y * MINIMAP_TILE + dy;

					if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height)
						mlx_put_pixel(img, px, py, color);
				}
			}
		}
	}

	// рисуем игрока
	int hero_px = MINIMAP_MARGIN + (int)(game->map->hero.x / TILE_SIZE * MINIMAP_TILE);
	int hero_py = MINIMAP_MARGIN + (int)(game->map->hero.y / TILE_SIZE * MINIMAP_TILE);

	for (int dy = -2; dy <= 2; dy++)
	{
		for (int dx = -2; dx <= 2; dx++)
		{
			int px = hero_px + dx;
			int py = hero_py + dy;

			if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height)
				mlx_put_pixel(img, px, py, 0xFF0000FF); // красная точка
		}
	}
}
