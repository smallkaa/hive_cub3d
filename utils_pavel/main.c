#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct s_map
{
    char        *area;
    int         size_x;
    int         size_y;
} t_map;

// Прототипы
void init_map(t_map *map);
void print_map(t_map *map, int player_x, int player_y);
void print_map_with_leak(t_map *map, int px, int py, int lx, int ly);
void print_map_with_islands(t_map *original_map, t_map *flooded_map, int px, int py);
bool is_map_closed(t_map *map, int start_x, int start_y, int *exit_x, int *exit_y);
bool is_map_fully_accessible(t_map *map, t_map *map_copy, int start_x, int start_y);


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


// --- Проверка на замкнутость карты ---

static bool can_reach_edge(t_map *map_copy, int x, int y, int *exit_x, int *exit_y)
{
    if (x <= 0 || x >= map_copy->size_x - 1 || y <= 0 || y >= map_copy->size_y - 1) {
        if (map_copy->area[y * map_copy->size_x + x] != '1') {
            *exit_x = x; *exit_y = y; return (true);
        }
        return (false);
    }
    char *cell = &map_copy->area[y * map_copy->size_x + x];
    if (*cell == '1' || *cell == 'F' || isspace((unsigned char)*cell)) return (false);
    *cell = 'F';
    return (can_reach_edge(map_copy, x + 1, y, exit_x, exit_y) ||
            can_reach_edge(map_copy, x - 1, y, exit_x, exit_y) ||
            can_reach_edge(map_copy, x, y + 1, exit_x, exit_y) ||
            can_reach_edge(map_copy, x, y - 1, exit_x, exit_y));
}

bool is_map_closed(t_map *map, int start_x, int start_y, int *exit_x, int *exit_y)
{
    if (!map || !map->area) return (false);
    if (start_x <= 0 || start_x >= map->size_x - 1 || start_y <= 0 || start_y >= map->size_y - 1) {
        *exit_x = start_x; *exit_y = start_y; return (false);
    }
    t_map map_copy = { .size_x = map->size_x, .size_y = map->size_y, .area = malloc(map->size_x * map->size_y) };
    if (!map_copy.area) return (false);
    memcpy(map_copy.area, map->area, map->size_x * map->size_y);
    bool reached_edge = can_reach_edge(&map_copy, start_x, start_y, exit_x, exit_y);
    free(map_copy.area);
    return (!reached_edge);
}

// --- Проверка на доступность всех ячеек ---

static int flood_fill(t_map *map_copy, int x, int y)
{
    if (x < 0 || x >= map_copy->size_x || y < 0 || y >= map_copy->size_y ||
        map_copy->area[y * map_copy->size_x + x] != '0')
        return (0);
    map_copy->area[y * map_copy->size_x + x] = 'F';
    return (1 + flood_fill(map_copy, x + 1, y) + flood_fill(map_copy, x - 1, y) +
            flood_fill(map_copy, x, y + 1) + flood_fill(map_copy, x, y - 1));
}

bool is_map_fully_accessible(t_map *map, t_map *map_copy, int start_x, int start_y)
{
    if (!map || !map->area || !map_copy) return (false);
    int total_zeros = 0;
    for (int i = 0; i < map->size_x * map->size_y; ++i)
        if (map->area[i] == '0') total_zeros++;
    if (total_zeros == 0) return (true);

    memcpy(map_copy->area, map->area, map->size_x * map->size_y);
    int accessible_count = flood_fill(map_copy, start_x, start_y);
    
    return (accessible_count == total_zeros);
}


int main(void)
{
    t_map   game_map;
    int     player_start_x = 30;
    int     player_start_y = 8;
    int     leak_x = -1, leak_y = -1;

    init_map(&game_map);
    printf("Карта успешно инициализирована (размер %d x %d).\n", game_map.size_x, game_map.size_y);

    print_map(&game_map, player_start_x, player_start_y);

    printf("Проверка замкнутости карты... ");
    if (!is_map_closed(&game_map, player_start_x, player_start_y, &leak_x, &leak_y)) {
        printf("[Error]\nКарта не замкнута. Обнаружен выход в точке (%d, %d).\n", leak_x, leak_y);
        print_map_with_leak(&game_map, player_start_x, player_start_y, leak_x, leak_y);
        free(game_map.area);
        return (1);
    }
    printf("[OK]\n");

    printf("Проверка доступности всех областей... ");
    t_map flooded_map = { .size_x = game_map.size_x, .size_y = game_map.size_y, .area = malloc(game_map.size_x * game_map.size_y) };
    if (!flooded_map.area) { free(game_map.area); return (1); }

    if (!is_map_fully_accessible(&game_map, &flooded_map, player_start_x, player_start_y)) {
        printf("[Error]\nНа карте есть недоступные области.\n");
        print_map_with_islands(&game_map, &flooded_map, player_start_x, player_start_y);
        free(flooded_map.area);
        free(game_map.area);
        return (1);
    }
    printf("[OK]\n");
    free(flooded_map.area);

    printf("\n🎉 Карта прошла все проверки и полностью валидна!\n");

    free(game_map.area);
    return (0);
}