/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:00:46 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/08/29 11:20:16 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** @brief  Create a clean copy of a path string.
** @details Skips leading spaces, removes trailing spaces and '\n',
**          then duplicates the trimmed path into a new string.
** @return  Pointer to new allocated string, or NULL on error.
*/
char	*dup_trim_path(const char *line)
{
	size_t	n;
	char	*new_line;

	while (*line == ' ' || *line == '\t')
		line++;
	n = ft_strlen(line);
	while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == ' '))
		n--;
	if (n == 0)
		return (NULL);
	new_line = malloc(n + 1);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, line, n);
	new_line[n] = '\0';
	return (new_line);
}

/*
** @brief  Assign a texture path if not already set.
** @details Checks for duplicates, trims the path string with dup_trim_path(),
**          and stores it in *dst.
** @return  0 on success, -1 on error or duplicate.
*/
int	set_path(char **dst, const char *rhs)
{
	if (*dst)
		return (err_msg("duplicate texture"), -1);
	*dst = dup_trim_path(rhs);
	if (!*dst || **dst == '\0')
		return (err_msg("invalid or empty texture path"), -1);
	return (0);
}
