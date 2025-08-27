/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pavel Vershinin <pvershin@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:27:29 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/27 20:27:30 by Pavel Versh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Processes a single row of pixels for texture resizing.
 * @details
 * 1. Calculates the source y-coordinate (`src_y`) corresponding to the
 *    destination y-coordinate.
 * 2. Iterates through each pixel `x` in the destination row.
 * 3. Calculates the source x-coordinate (`src_x`).
 * 4. Calculates the index (`sidx`) for the source pixel in the texture's
 *    pixel array.
 * 5. Copies the pixel color from source to destination.
 * @param v The resize variables struct.
 * @param y The current y-coordinate in the destination image.
 */
static void	process_row(t_resize_vars *v, int y)
{
	int			x;
	int			src_x;
	int			src_y;
	size_t		sidx;
	uint32_t	pix;

	src_y = (int)((long long)y * v->tex->height / v->new_h);
	x = 0;
	while (x < v->new_w)
	{
		src_x = (int)((long long)x * v->tex->width / v->new_w);
		sidx = ((size_t)src_y * v->tex->width + src_x) * 4;
		pix = *(const uint32_t *)(v->tex->pixels + sidx);
		((uint32_t *)v->img->pixels)[y * v->new_w + x] = pix;
		x++;
	}
}

/**
 * @brief Resizes a texture to a new width and height.
 * @details
 * 1. Validates input parameters.
 * 2. Creates a new `mlx_image_t` with the specified dimensions.
 * 3. Initializes a `t_resize_vars` struct with image and texture data.
 * 4. Iterates through each row `y` of the new image.
 * 5. Calls `process_row` for each row to copy pixel data.
 * 6. Returns the newly created and resized image.
 * @param mlx The MLX42 instance.
 * @param tex The source texture.
 * @param new_w The new width.
 * @param new_h The new height.
 * @return A new mlx_image_t with the resized texture, or NULL on failure.
 */
static mlx_image_t	*resize_tex_to_image(mlx_t *mlx,
	const mlx_texture_t *tex, int new_w, int new_h)
{
	t_resize_vars	vars;
	int				y;

	if (new_w <= 0 || new_h <= 0 || !mlx || !tex || !tex->pixels)
		return (NULL);
	vars.img = mlx_new_image(mlx, new_w, new_h);
	if (!vars.img)
		return (NULL);
	vars.tex = tex;
	vars.new_w = new_w;
	vars.new_h = new_h;
	y = 0;
	while (y < new_h)
	{
		process_row(&vars, y);
		y++;
	}
	return (vars.img);
}

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
 * @brief Loads and resizes the wand texture.
 * @details
 * 1. Validates input parameters.
 * 2. Loads the wand PNG from the specified path.
 * 3. Calls `resize_tex_to_image` to resize it to `WAND_W`x`WAND_H`.
 * 4. Deletes the original texture to free memory.
 * 5. Assigns the new image to `g->wand`.
 * 6. Returns 0 on success, -1 on failure.
 * @param g The game struct.
 * @param path The path to the wand texture.
 * @return 0 on success, -1 on failure.
 */
int	load_wand(t_game *g, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	if (!g || !path)
	{
		err_msg("load_wand: bad args");
		return (-1);
	}
	texture = mlx_load_png(path);
	if (!texture)
	{
		err_msg("Failed to load texture");
		return (-1);
	}
	img = resize_tex_to_image(g->mlx, texture, WAND_W, WAND_H);
	mlx_delete_texture(texture);
	if (!img)
	{
		err_msg("Failed to convert wand texture to image");
		return (-1);
	}
	g->wand = img;
	return (0);
}

/**
 * @brief Loads all game textures.
 * @details
 * 1. Calls `load_texture_from_path` for the North (NO) texture.
 * 2. Calls `load_texture_from_path` for the South (SO) texture.
 * 3. Calls `load_texture_from_path` for the West (WE) texture.
 * 4. Calls `load_texture_from_path` for the East (EA) texture.
 * 5. Calls `load_wand` for the wand texture.
 * 6. Returns -1 if any loading operation fails, otherwise returns 0.
 * @param g The game struct.
 * @return 0 on success, -1 on failure.
 */
int	load_all_textures(t_game *g)
{
	if (load_texture_from_path(&g->tx.tex[TEX_NO], g->map->no) < 0)
	{
		return (-1);
	}
	if (load_texture_from_path(&g->tx.tex[TEX_SO], g->map->so) < 0)
	{
		return (-1);
	}
	if (load_texture_from_path(&g->tx.tex[TEX_WE], g->map->we) < 0)
	{
		return (-1);
	}
	if (load_texture_from_path(&g->tx.tex[TEX_EA], g->map->ea) < 0)
	{
		return (-1);
	}
	if (load_wand(g, WAND) < 0)
	{
		return (-1);
	}
	return (0);
}
