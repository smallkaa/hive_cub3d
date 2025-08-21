#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>













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