#include "cub3D.h"

static char	getmapitem(t_map *map, int x, int y)
{
	int	line_len;

	if (y < 0 || y >= map->size_y || !map->area[y])
		return ('\0');
	line_len = ft_strlen(map->area[y]);
	if (x < 0 || x >= line_len)
		return (' ');
	return (map->area[y][x]);
}

/*
** @brief      Recursive flood fill algorithm to check for map openings.
**
** @param      map_copy  A temporary copy of the map area.
** @param      pos       The current coordinates (x, y) to check.
** @param      dims      The dimensions (width, height) of the map copy.
**
** @return     Returns false if the fill reaches a space or the map boundary,
** indicating the map is not closed. Otherwise, returns true.
*/
static bool	flood_fill(char **map_copy, t_point pos, t_point dims)
{
	if (pos.y < 0 || pos.y >= dims.y || pos.x < 0 || pos.x >= dims.x)
		return (false);
	if (map_copy[pos.y][pos.x] == ' ')
		return (false);
	if (map_copy[pos.y][pos.x] == '1' || map_copy[pos.y][pos.x] == 'F')
		return (true);
	map_copy[pos.y][pos.x] = 'F';
	if (!flood_fill(map_copy, (t_point){pos.x + 1, pos.y}, dims) || \
		!flood_fill(map_copy, (t_point){pos.x - 1, pos.y}, dims) || \
		!flood_fill(map_copy, (t_point){pos.x, pos.y + 1}, dims) || \
		!flood_fill(map_copy, (t_point){pos.x, pos.y - 1}, dims))
	{
		return (false);
	}
	return (true);
}

/*
** @brief      Finds the maximum width of the map.
**
** @param      map   The map structure.
**
** @return     The length of the longest line in the map area.
*/
static int	get_max_width(t_map *map)
{
	int	max_width;
	int	current_width;
	int	y;

	y = 0;
	max_width = 0;
	while (y < map->size_y)
	{
		if (map->area[y])
		{
			current_width = ft_strlen(map->area[y]);
			if (current_width > max_width)
				max_width = current_width;
		}
		y++;
	}
	return (max_width);
}

/*
** @brief      Creates and populates a rectangular copy of the map.
**
** @param      map   The original map structure.
** @param      dims  The dimensions (width, height) for the new copy.
**
** @return     A pointer to the newly allocated and filled map copy,
** or NULL on allocation failure.
*/
static char	**create_map_copy(t_map *map, t_point dims)
{
	char	**copy;
	int		x;
	int		y;

	copy = ft_calloc(dims.y + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < dims.y)
	{
		copy[y] = ft_calloc(dims.x + 1, sizeof(char));
		if (!copy[y])
		{
			free_area(copy, y);
			return (NULL);
		}
		x = 0;
		while (x < dims.x)
		{
			copy[y][x] = getmapitem(map, x, y);
			x++;
		}
		y++;
	}
	return (copy);
}

/*
** @brief      Checks if the map is enclosed by walls.
**
** It creates a rectangular copy of the map, then uses a
** flood fill algorithm starting from the player's position
** to see if any open space ('0' or player) touches a boundary
** or a space character.
**
** @param      map   The map structure to check.
**
** @return     True if the map is properly closed, false otherwise.
*/
bool	is_map_closed(t_map *map)
{
	char	**map_copy;
	bool	is_closed;
	t_point	dims;
	t_point	start_pos;

	dims.y = map->size_y;
	dims.x = get_max_width(map);
	if (dims.x <= 0 || dims.y <= 0)
		return (false);
	map_copy = create_map_copy(map, dims);
	if (!map_copy)
	{
		err_msg("failed to create map copy for validation");
		return (false);
	}
	start_pos.x = (int)map->hero.x;
	start_pos.y = (int)map->hero.y;
	is_closed = flood_fill(map_copy, start_pos, dims);
	free_area(map_copy, dims.y);
	if (!is_closed)
		err_msg("map is not closed by walls");
	return (is_closed);
}
