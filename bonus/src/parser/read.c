/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:27:54 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/08/28 13:27:06 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_number(const char *str, int *i)
{
	int	num;

	num = 0;
	*i = skip_spaces(str, *i);
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		num = num * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (num);
}

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

/*
** @brief  Reads lines from .cub file into map->area.
** @details Opens file, reads up to max_lines with get_next_line(),
**          trims '\n', duplicates into map->area, and NULL-terminates.
** @return  Number of lines read on success, -1 on error.
*/
int	read_map(t_map *map, char *filename, int max_lines, int i)
{
	int		fd;
	char	*line;
	char	*nl;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (i < max_lines)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		map->area[i] = ft_strdup(line);
		free(line);
		if (!map->area[i])
			return (close(fd), err_msg("memory error"), -1);
		i++;
	}
	close(fd);
	if (i < max_lines)
		map->area[i] = NULL;
	return (i);
}
