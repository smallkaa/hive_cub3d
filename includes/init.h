#ifndef INIT_H
# define INIT_H

#include "cub3D.h"

typedef struct s_hero
{
	double		x;
	double		y;
	double		angle;
} t_hero;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	uint32_t	floor_c;
	uint32_t	ceil_c;
	char		**area;
	int			size_x;
	int			size_y;
	t_hero		hero;
	// t_point		exit_pos;
}				t_map;

// typedef struct s_mini
// {
//     float   dx;         // Delta X position
//     float   dy;         // Delta Y position  
//     float   rdx;        // Rotated delta X
//     float   rdy;        // Rotated delta Y
//     float   map_x;      // Map X coordinate
//     float   map_y;      // Map Y coordinate
//     int     tile_x;     // Tile X index
//     int     tile_y;     // Tile Y index
// }               t_mini;

// typedef struct s_minimap
// {
//    //mlx_image_t *img;
//     int         radius;
//     int         scale;
//     int         center_x;   // Center position on screen
//     int         center_y;
// }               t_minimap;

typedef enum e_face 
{ 
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3,
} t_face;

typedef struct s_textures
{
	mlx_texture_t *tex[4];   // NO, SO, WE, EA (raw PNGs)
} t_textures;

typedef struct s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	plx;
	double	ply;
	double	rx;
	double	ry;
	int		mapx;
	int		mapy;
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	int		stepx;
	int		stepy;
	int		side;
	double	perp;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*wand;
	t_map		*map;
	t_textures	tx;
	t_ray		ray;
	mlx_image_t	*minimap; // delete it from mandotory part
}				t_game;

typedef struct s_pixel_data
{
    int			x;
    int			y;
    int			y0;
    int			y1;
}	t_pixel_data;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_stripe_data
{
	int				x;
	int				height;
	int				y0;
	int				y1;
	t_face			face;
	mlx_texture_t	*tex;
	int				tex_x;
}	t_stripe_data;


#endif