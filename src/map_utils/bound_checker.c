#include "../includes/cub3D.h"

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