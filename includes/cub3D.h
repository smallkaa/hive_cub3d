#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

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

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;

}				t_game;

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



// Прототипы
void init_map(t_map *map);
void print_map(t_map *map, int player_x, int player_y);
void print_map_with_leak(t_map *map, int px, int py, int lx, int ly);
void print_map_with_islands(t_map *original_map, t_map *flooded_map, int px, int py);
bool is_map_closed(t_map *map, int start_x, int start_y, int *exit_x, int *exit_y);
bool is_map_fully_accessible(t_map *map, t_map *map_copy, int start_x, int start_y);

// utils
void			err_msg(char *msg);
void			free_area(char **area, int n);
void			free_map(t_map *map);

// parsing

int				read_map(t_map *map, const char *filename, int max_lines,
					int i);
int				count_lines(char *filename);
t_map			*parsing_args(char *filename);
int				symbols_check(t_map *map, int map_start);
int				find_map_start(t_map *map);
int				parse_identifier_line(t_map *map, const char *line);
bool			is_map_line(const char *line);
bool			is_valid_symbol(char c);
int				skip_spaces(const char *str, int i);
int				player_check(t_map *map, int map_start);
void			render_view(t_game *game);
void			setup_input(t_game *game);
void	draw_background(t_game *game);


#endif