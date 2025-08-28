/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:27:29 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/28 14:22:15 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Loads a single PNG texture from a path.
 * @details
 * 1. Uses `mlx_load_png` to load the texture from the given path.
 * 2. If loading fails, prints an error message and returns -1.
 * 3. Returns 0 on success.
 * @param slot The slot to store the loaded texture in.
 * @param path The path to the PNG file.
 * @return 0 on success, -1 on failure.
 */
static int	load_texture_from_path(mlx_texture_t **slot, const char *path)
{
	*slot = mlx_load_png(path);
	if (!*slot)
	{
		err_msg("Failed to load texture");
		return (-1);
	}
	return (0);
}

/**
 * @brief Loads all game textures.
 * @details
 * 1. Calls `load_texture_from_path` for the North (NO) texture.
 * 2. Calls `load_texture_from_path` for the South (SO) texture.
 * 3. Calls `load_texture_from_path` for the West (WE) texture.
 * 4. Calls `load_texture_from_path` for the East (EA) texture.
 * 5. Returns -1 if any loading operation fails, otherwise returns 0.
 * @param g The game struct.
 * @return 0 on success, -1 on failure.
 */
int	load_all_textures(t_game *g)
{
	if (load_texture_from_path(&g->tx.tex[TEX_NO], g->map->no) < 0)
		return (-1);
	if (load_texture_from_path(&g->tx.tex[TEX_SO], g->map->so) < 0)
		return (-1);
	if (load_texture_from_path(&g->tx.tex[TEX_WE], g->map->we) < 0)
		return (-1);
	if (load_texture_from_path(&g->tx.tex[TEX_EA], g->map->ea) < 0)
		return (-1);
	return (0);
}
