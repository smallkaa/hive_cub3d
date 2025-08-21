#include "cub3D.h"

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