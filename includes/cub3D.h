
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define WALL "./textures/1.png"
# define FLOOR "./textures/2.png"
# define EXIT "./textures/3.png"
# define PLAYER "./textures/4.png"


typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_map
{
	char		**area;
	int			size_x;
	int			size_y;
	t_point		player_pos;
	t_point		exit_pos;
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

//utils
void	err_msg(char *msg);
void	free_area(char **area, int n);
void	free_map(t_map *map);

//parsing
t_map	*parsing_args(char *filename);

#endif
