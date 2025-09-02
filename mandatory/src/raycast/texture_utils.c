/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvershin <pvershin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:56 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/09/02 10:06:40 by pvershin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Determines which texture to use based on the wall side hit by a ray.
 * @details
 * 1. Checks if the ray hit a vertical wall (`r->side == 0`).
 * 2. If vertical, checks the ray's x-direction (`r->stepx`) to determine
 *    if it's an East or West wall.
 * 3. If horizontal, checks the ray's y-direction (`r->stepy`) to determine
 *    if it's a South or North wall.
 * 4. Returns the corresponding texture face enum.
 * @param r The ray struct.
 * @return The texture face (TEX_NO, TEX_SO, TEX_WE, TEX_EA).
 */
t_face	determine_wall_face(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->stepx > 0)
			return (TEX_WE);
		else
			return (TEX_EA);
	}
	else
	{
		if (r->stepy > 0)
			return (TEX_SO);
		else
			return (TEX_NO);
	}
}

/**
 * @brief Gets the color of a pixel from a texture at a given coordinate.
 * @details
 * 1. Validates that the texture exists and the coordinates are within bounds.
 * 2. Calculates the pointer to the start of the desired pixel in the
 *    texture's pixel data array.
 * 3. Combines the RGBA components into a single `uint32_t` color value.
 * 4. Returns the calculated color.
 * @param tex The texture.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return The color of the pixel in uint32_t format.
 */
uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixel;

	if (!tex || x < 0 || x >= (int)tex->width)
	{
		return (0xFF000000);
	}
	if (y < 0 || y >= (int)tex->height)
	{
		return (0xFF000000);
	}
	pixel = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return ((uint32_t)pixel[0] << 24
		| (uint32_t)pixel[1] << 16
		| (uint32_t)pixel[2] << 8
		| (uint32_t)pixel[3]);
}
