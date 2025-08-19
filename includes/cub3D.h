
#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WALL "./textures/1.png"
# define FLOOR "./textures/2.png"
# define EXIT "./textures/3.png"
# define PLAYER "./textures/4.png"

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

// typedef struct s_rgb
// {
// 	int r, g, b;
// 	int set; // 0/1
// }				t_rgb;

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
	t_point		player_pos;
	// t_point		exit_pos;
}				t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_coll;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_player;
	mlx_image_t	*img_enemy;
}				t_game;

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
int				player_check(t_map *map, int map_start);

#endif
