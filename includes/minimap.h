#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

# define MM_TILE      8        // pixels per map cell on minimap
# define MM_MARGIN_X  12       // screen offset
# define MM_MARGIN_Y  12
# define MM_FOV_LEN   14       // length of facing line (in pixels)
# define MM_ALPHA(a,r,g,b) ((uint32_t)((a)<<24 | (r)<<16 | (g)<<8 | (b)))
# define MAX_MINIMAP_SIZE 300 
#define MINIMAP_RADIUS    60    // Size of circular minimap
#define MINIMAP_SCALE     4     // Scale factor 
#define NORTH_POV         0     // North orientation
#define TILE_SIZE         1     // Your grid tile

// struct s_game;

// typedef struct s_minimap
// {
// 	mlx_image_t *img;
// 	int			w;   // pixel width
// 	int			h;   // pixel height
// 	int			ox;  // on-screen x
// 	int			oy;  // on-screen y
// } t_minimap;

int  minimap_init(t_game *g, t_minimap *mm);
void minimap_draw(t_game *g, t_minimap *mm);

#endif
