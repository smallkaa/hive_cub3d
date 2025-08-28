/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawtexture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Pavel Vershinin <pvershin@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:32 by Pavel Versh       #+#    #+#             */
/*   Updated: 2025/08/27 20:26:33 by Pavel Versh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
** @brief      Calculates the texture's X-coordinate for a wall stripe.
** @details    This function determines which vertical line of the texture
** should be drawn on the screen for the current wall segment.
**
** 1. **Calculate Wall Hit Position (`wall_x`):**
** - If a vertical wall was hit (`side == 0`), the exact
** y-coordinate of the hit is calculated.
** - If a horizontal wall was hit (`side == 1`), the exact
** x-coordinate of the hit is calculated.
**
** 2. **Normalize the Hit Position:**
** - The `wall_x` value is normalized to a fraction between 0.0
** and 1.0 by subtracting its integer part (`floor`). This
** represents how far along the wall tile the ray hit.
**
** 3. **Scale to Texture Width:**
** - The normalized `wall_x` is multiplied by the texture's
** width to get the corresponding column of the texture
** (`tex_x`).
**
** 4. **Correct Texture Mirroring:**
** - The texture coordinates are flipped if the ray is moving
** from right-to-left or from bottom-to-top. This ensures
** that the texture is not rendered as a mirror image
** depending on the player's viewing direction.
*/
static int	calculate_texture_x(t_ray *r, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = r->posy + r->perp * r->ry;
	else
		wall_x = r->posx + r->perp * r->rx;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (r->side == 0 && r->rx > 0)
		tex_x = tex->width - tex_x - 1;
	if (r->side == 1 && r->ry < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

/*
** @brief      Initializes drawing parameters for a single vertical wall stripe.
** @details    This function sets up all the necessary data to render one
** vertical column of a wall based on the raycasting results.
**
** 1. **Calculate Projected Height:**
** - `s->height` is calculated based on the perpendicular
** distance (`r->perp`) to the wall. The further the wall,
** the smaller its projected height on the screen.
**
** 2. **Determine Vertical Drawing Boundaries:**
** - `s->y0` (start y) and `s->y1` (end y) are calculated to
** define the top and bottom pixels of the wall stripe on the
** screen. The calculation centers the stripe vertically.
**
** 3. **Select the Correct Wall Face:**
** - `determine_wall_face(r)` is called to determine which side of a map
** cell was hit (North, South, West, or East).
**
** 4. **Assign the Appropriate Texture:**
** - The corresponding texture (`s->tex`) is selected from the
** game's texture array based on the determined face.
**
** 5. **Calculate Texture's X-Coordinate:**
** - `calculate_texture_x` is called to find the specific
** vertical column of the texture (`s->tex_x`) that needs to
** be drawn for this stripe.
*/
static void	init_stripe(t_game *g, t_ray *r, t_stripe_data *s)
{
	s->height = (int)((double)WINDOW_HEIGHT / r->perp);
	s->y0 = -s->height / 2 + WINDOW_HEIGHT / 2;
	s->y1 = s->height / 2 + WINDOW_HEIGHT / 2;
	s->face = determine_wall_face(r);
	s->tex = g->tx.tex[s->face];
	s->tex_x = calculate_texture_x(r, s->tex);
}

/*
** @brief      Renders a single vertical column of a texture to the screen.
** @details    This function iterates through the vertical pixels of a wall
** stripe, samples the corresponding pixels from the texture,
** and draws them to the screen image.
**
** 1. **Calculate Texture Step Size (`tex_step`):**
** - Determines how much the texture's y-coordinate (`tex_pos`)
** should increment for each pixel drawn on the screen.
** - If the wall stripe is taller than the texture, this value
** will be less than 1 (texture is stretched).
** - If the wall stripe is shorter, it will be greater than 1
** (texture is compressed).
**
** 2. **Set Initial Texture Position (`tex_pos`):**
** - If the wall stripe starts above the screen's top edge
** (`s->y0 < 0`), this calculates the correct starting
** y-position within the texture to avoid drawing the unseen
** part of the wall.
**
** 3. **Loop Through Vertical Pixels:**
** - The loop runs from the stripe's starting y-pixel (`s->y0`)
** to its ending y-pixel (`s->y1`), ensuring it stays
** within the window's vertical boundaries.
**
** 4. **Map Screen Y to Texture Y:**
** - `tex_y` is calculated by converting the floating-point
** texture position `tex_pos` to an integer. This gives the
** row of pixels to sample from the texture.
**
** 5. **Get and Draw Pixel Color:**
** - `get_texture_pixel` retrieves the color of the pixel at
** (`s->tex_x`, `tex_y`) from the texture.
** - `mlx_put_pixel` draws the retrieved color onto the main
** image at the current screen coordinates (`x`, `y`).
**
** 6. **Increment Texture Position:**
** - `tex_pos` is incremented by `tex_step` to prepare for the
** next pixel in the column, effectively moving down the
** texture.
*/
static void	draw_texture_column(t_game *g, t_stripe_data *s, int x)
{
	double		tex_pos;
	double		tex_step;
	int			y;
	int			tex_y;
	uint32_t	color;

	tex_step = 1.0 * s->tex->height / s->height;
	tex_pos = 0.0;
	if (s->y0 < 0)
		tex_pos = -s->y0 * tex_step;
	y = s->y0;
	if (y < 0)
		y = 0;
	while (y <= s->y1 && y < WINDOW_HEIGHT)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)s->tex->height)
			tex_y = s->tex->height - 1;
		color = get_texture_pixel(s->tex, s->tex_x, tex_y);
		mlx_put_pixel(g->img, x, y, color);
		tex_pos += tex_step;
		y++;
	}
}

void	draw_stripe(t_game *g, int x, t_ray *r)
{
	t_stripe_data	s;

	init_stripe(g, r, &s);
	if (!s.tex)
		return ;
	draw_texture_column(g, &s, x);
}
