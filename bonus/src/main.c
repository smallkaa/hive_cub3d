/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvershin <pvershin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:16 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/29 12:58:24 by pvershin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_map	*map;
	t_game	game;

	if (ac != 2)
		return (err_msg("Usage: ./cub3D <file.cub>"), 1);
	map = parsing_args(av[1]);
	if (!map)
		return (1);
	convert_hero_to_pixels(map);
	game.map = map;
	if (game_loop(&game) < 0)
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}
