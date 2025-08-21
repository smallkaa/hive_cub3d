/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:25:16 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/08/21 14:57:38 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_join(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	if ((!s1 || !*s1) && (!s2 || !*s2))
		return (NULL);
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, s1_len);
	if (s2)
		ft_memcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

char	*find_newline(const char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	char	*remaining;

	if (!buffer || !*buffer)
		return (NULL);
	newline_pos = find_newline(*buffer);
	if (newline_pos)
	{
		line = malloc(newline_pos - *buffer + 2);
		if (!line)
			return (NULL);
		ft_memcpy(line, *buffer, newline_pos - *buffer + 1);
		line[newline_pos - *buffer + 1] = '\0';
		remaining = str_join(NULL, newline_pos + 1);
		free(*buffer);
		*buffer = remaining;
	}
	else
	{
		line = str_join(NULL, *buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (free(buffer), NULL);
	bytes_read = 1;
	while (!find_newline(buffer) && bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		buffer = str_join(buffer, temp_buffer);
		if (!buffer)
			break ;
	}
	free(temp_buffer);
	if (bytes_read < 0 || !buffer)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
