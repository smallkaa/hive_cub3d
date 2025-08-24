#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

// # define MM_TILE      8        // pixels per map cell on minimap
// # define MM_MARGIN_X  12       // screen offset
// # define MM_MARGIN_Y  12
// # define MM_FOV_LEN   14       // length of facing line (in pixels)
// # define MM_ALPHA(a,r,g,b) ((uint32_t)((a)<<24 | (r)<<16 | (g)<<8 | (b)))
// # define MAX_MINIMAP_SIZE 300 
// #define MINIMAP_RADIUS    60    // Size of circular minimap
// #define MINIMAP_SCALE     4     // Scale factor 
// #define NORTH_POV         0     // North orientation
//#define TILE_SIZE         1     // Your grid tile

# define MINIMAP_TILE 8      // размер клетки на миникарте (в пикселях)
# define MINIMAP_MARGIN 5
#define WALL_COLOR     0x006666FF
#define FLOOR_COLOR    0x222222FF
#define HERO_COLOR     0xFF0000FF
#define BACKGROUND     0x00FFCCFF
#define HERO_COLOR 0xFF0000FF // red, no opasity


typedef struct s_mini
{
	float   dx;         // Delta X position
	float   dy;         // Delta Y position  
	float   rdx;        // Rotated delta X
	float   rdy;        // Rotated delta Y
	float   map_x;      // Map X coordinate
	float   map_y;      // Map Y coordinate
	int     tile_x;     // Tile X index
	int     tile_y;     // Tile Y index
}               t_mini;

typedef struct s_minimap
{
   //	mlx_image_t *img;
	int         radius;
	int         scale;
	int         center_x;   // Center position on screen
	int         center_y;
}               t_minimap;

int  minimap_init(t_game *g);

void draw_minimap(t_game *game);


#endif
