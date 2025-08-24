#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include "libft.h"
# include "init.h"
# include "minimap.h"

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

#define TILE_SIZE 64
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define WAND_W  400
# define WAND_H  400
# define WAND "./assets/wand.png"
# define MINIMAP_RADIUS    60
# define MINIMAP_SCALE     4
# define NORTH_POV         0
//# define TILE_SIZE         1
# define MM_ALPHA(a,r,g,b) ((uint32_t)((a)<<24 | (r)<<16 | (g)<<8 | (b)))

// struct s_minimap;
// struct s_game;


// Прототипы
void init_map(t_map *map);
void print_map(t_map *map, int player_x, int player_y);
//void print_map_with_leak(t_map *map, int px, int py, int lx, int ly);
//void print_map_with_islands(t_map *original_map, t_map *flooded_map, int px, int py);
// bool is_map_closed(t_map *map, int start_x, int start_y, int *exit_x, int *exit_y);
// bool is_map_fully_accessible(t_map *map, t_map *map_copy, int start_x, int start_y);

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
void			draw_background(t_game *game);
void			game_loop(t_game *game);
bool			is_map_closed(t_map *map);

//game
int	load_all_textures(t_game *g);
t_face pick_face(t_ray *r);
uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y);
void handle_movement(t_game *game);
void move_forward_backward(t_game *game, int forward);
void move_left_right(t_game *game, int left);
void rotate_player(t_game *game, int left);
void convert_hero_to_pixels(t_map *map);

// Function declarations

#endif