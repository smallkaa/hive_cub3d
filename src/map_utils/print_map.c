#include "../includes/cub3D.h"

void print_map(t_map *map, int player_x, int player_y)
{
    printf("--- Визуализация карты ---\n");
    for (int y = 0; y < map->size_y; y++) {
        for (int x = 0; x < map->size_x; x++) {
            if (x == player_x && y == player_y) printf("\033[1;32mP\033[0m");
            else putchar(map->area[y * map->size_x + x]);
        }
        putchar('\n');
    }
    printf("--------------------------\n");
}

void print_map_with_leak(t_map *map, int px, int py, int lx, int ly)
{
    printf("--- Визуализация утечки ---\n");
    for (int y = 0; y < map->size_y; y++) {
        for (int x = 0; x < map->size_x; x++) {
            if (x == px && y == py) printf("\033[1;32mP\033[0m");
            else if (x == lx && y == ly) printf("\033[1;31mX\033[0m");
            else putchar(map->area[y * map->size_x + x]);
        }
        putchar('\n');
    }
    printf("---------------------------\n");
}

/**
 * @brief Печатает карту, отмечая игрока (P) и недоступные "острова" (I).
 */
void print_map_with_islands(t_map *original_map, t_map *flooded_map, int px, int py)
{
    printf("--- Визуализация недоступных областей ---\n");
    for (int y = 0; y < original_map->size_y; y++) {
        for (int x = 0; x < original_map->size_x; x++) {
            int index = y * original_map->size_x + x;
            if (x == px && y == py) {
                printf("\033[1;32mP\033[0m"); // Игрок
            } else if (original_map->area[index] == '0' && flooded_map->area[index] == '0') {
                printf("\033[1;33mI\033[0m"); // 'I' - Island (остров)
            } else {
                putchar(original_map->area[index]);
            }
        }
        putchar('\n');
    }
    printf("------------------------------------------\n");
}