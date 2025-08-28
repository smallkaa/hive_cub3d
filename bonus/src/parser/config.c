/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:28:34 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/28 16:13:56 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** @brief  Parse "R,G,B" string into a 32-bit ARGB color.
** @details Validates that each component is 0–255, enforces commas as 
**          separators, and packs values into uint32_t (R|G|B|Alpha).
** @return  Packed color (e.g. 0xRRGGBBFF) or 0xFFFFFFFF on error.
*/
static uint32_t	parse_color(const char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = parse_number(str, &i);
	i = skip_spaces(str, i);
	if (r < 0 || r > 255 || str[i++] != ',')
		return (0xFFFFFFFF);
	g = parse_number(str, &i);
	i = skip_spaces(str, i);
	if (g < 0 || g > 255 || str[i++] != ',')
		return (0xFFFFFFFF);
	b = parse_number(str, &i);
	if (b < 0 || b > 255)
		return (0xFFFFFFFF);
	i = skip_spaces(str, i);
	if (str[i] != '\0' && str[i] != '\n')
		return (0xFFFFFFFF);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/*
** @brief      Parses a texture identifier line (NO, SO, WE, EA).
** @details    - Skips the identifier ("NO", "SO", "WE", "EA") and ensures it is
**                followed by at least one space.
**             - Verifies the texture has not already been set 
**                (duplicate check).
**             - Calls set_path() to store the texture path.
**             - Returns 1 (true) on success.
**             - Returns 0 (false) and prints an error message if the line is
**                invalid or a duplicate is detected.
**
** @param      map   Pointer to the map structure being filled.
** @param      line  The current configuration line.
**
** @return     1 on success, 0 on fail(not a texture line).
*/
static int	parse_texture_line(t_map *map, const char *line)
{
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
	{
		if (map->no)
			return (err_msg("duplicate north texture"), 0);
		return (set_path(&map->no, line + 2));
	}
	if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
	{
		if (map->so)
			return (err_msg("duplicate south texture"), 0);
		return (set_path(&map->so, line + 2));
	}
	if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
	{
		if (map->we)
			return (err_msg("duplicate west texture"), 0);
		return (set_path(&map->we, line + 2));
	}
	if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
	{
		if (map->ea)
			return (err_msg("duplicate east texture"), 0);
		return (set_path(&map->ea, line + 2));
	}
	return (0);
}

/*
** @brief      Parses a color identifier line (F for floor, C for ceiling).
** @details    - Ensures the identifier is followed by a space.
**             - Verifies the color has not already been set (duplicate check).
**             - Calls parse_color() to convert the R,G,B values into a packed
**                uint32_t color.
**             - Uses 0xFFFFFFFF as a sentinel for "unset" or "invalid".
**             - Returns 1 (true) on success.
**             - Returns 0 (false) and prints an error message if the line is
**                invalid, a duplicate, or contains out-of-range values.
**
** @param      map   Pointer to the map structure being filled.
** @param      line  The current configuration line.
**
** @return     1 on success, 0 (not a color line).
*/
static int	parse_color_line(t_map *map, const char *line)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (map->floor_c != 0xFFFFFFFF)
			return (err_msg("duplicate floor color"), 0);
		map->floor_c = parse_color(line + 1);
		if (map->floor_c == 0xFFFFFFFF)
			return (err_msg("invalid floor color"), 0);
		return (1);
	}
	if (line[0] == 'C' && line[1] == ' ')
	{
		if (map->ceil_c != 0xFFFFFFFF)
			return (err_msg("duplicate ceiling color"), 0);
		map->ceil_c = parse_color(line + 1);
		if (map->ceil_c == 0xFFFFFFFF)
			return (err_msg("invalid ceiling color"), 0);
		return (1);
	}
	return (0);
}

int	parse_identifier_line(t_map *map, const char *line)
{
	if (ft_strchr(line, '\t'))
		return (err_msg("invalid character: tab not allowed"), 0);
	while (*line == ' ')
		line++;
	if (parse_texture_line(map, line))
		return (1);
	if (parse_color_line(map, line))
		return (1);
	return (0);
}
