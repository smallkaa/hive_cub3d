#include "cub3D.h"
static mlx_image_t *resize_tex_to_image(mlx_t *mlx, const mlx_texture_t *tex, int new_w, int new_h)
{
    int x;
	int y;
    uint32_t *dst32;
    const uint8_t *src = tex->pixels;

    if (new_w <= 0 || new_h <= 0 || !mlx || !tex || !src)
        return NULL;

    mlx_image_t *img = mlx_new_image(mlx, new_w, new_h);
    if (!img)
        return NULL;

    dst32 = (uint32_t *)img->pixels;
	y = 0;
    while (y < new_h)
    {
        // map destination y to source y
        int src_y = (int)((long long)y * tex->height / new_h);
        for (x = 0; x < new_w; x++)
        {
            int src_x = (int)((long long)x * tex->width / new_w);

            // 4 bytes per pixel (RGBA)
            size_t sidx = ((size_t)src_y * tex->width + src_x) * 4;

            // read as 32-bit to keep RGBA (including alpha)
            uint32_t pix = *(const uint32_t *)(src + sidx);

            dst32[y * new_w + x] = pix;
        }
		y++;
    }
    return img;
}

static int	load_one(mlx_texture_t **slot, const char *path)
{
	printf("Loading texture: %s\n", path);  // Debug
	*slot = mlx_load_png(path);
	if (!*slot)
	{
		printf("Failed to load: %s\n", path);  // Debug
		return (err_msg("Failed to load texture"), -1);
	}
	printf("Successfully loaded: %s (%dx%d)\n", path, (*slot)->width, (*slot)->height);  // Debug
	return (0);
}
int load_wand(t_game *g, char *path)
{
	printf("Loading wand...\n");
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	if (!g || !path)
        return (err_msg("load_wand: bad args"), -1);

	texture = mlx_load_png(path);
	if (!texture)
	{
		err_msg("Failed to load texture");
		return (-1);
	}
	img = resize_tex_to_image(g->mlx, texture, WAND_W, WAND_H);
	mlx_delete_texture(texture); 
	if (!img)
		return (err_msg("Failed to convert wand texture to image"), -1);
	
	g->wand = img;
	return (0);
}

int	load_all_textures(t_game *g)
{
	printf("Loading textures...\n");
	printf("NO: %s\n", g->map->no);
	printf("SO: %s\n", g->map->so);
	printf("WE: %s\n", g->map->we);
	printf("EA: %s\n", g->map->ea);

	if (load_one(&g->tx.tex[TEX_NO], g->map->no) < 0)
		return -1;
	if (load_one(&g->tx.tex[TEX_SO], g->map->so) < 0)
		return -1;
	if (load_one(&g->tx.tex[TEX_WE], g->map->we) < 0)
		return -1;
	if (load_one(&g->tx.tex[TEX_EA], g->map->ea) < 0)
		return -1;
	if (load_wand(g, WAND) < 0)
		return -1;
	printf("All textures loaded successfully!\n");
	return 0;
}



t_face pick_face(t_ray *r)
{
	if (r->side == 0)  // Hit vertical wall (NS walls)
	{
		if (r->stepx > 0)
			return TEX_EA;  // Moving east, hit east wall
		else
			return TEX_WE;  // Moving west, hit west wall
	}
	else  // Hit horizontal wall (EW walls)
	{
		if (r->stepy > 0)
			return TEX_SO;  // Moving south, hit south wall
		else
			return TEX_NO;  // Moving north, hit north wall
	}
}

uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	if (!tex || x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return 0xFF000000; // Black fallback
	
	uint8_t *pixel = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	
	// Convert RGBA to MLX42 format
	return (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
}