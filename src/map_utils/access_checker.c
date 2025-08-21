#include "../includes/cub3D.h"

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