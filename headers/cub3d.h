/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/04 21:38:05 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 42
# define BLUE 6591981
# define LAVENDER 15792383
# define GREEN 9419919
# define GRAY 14474460
# define PINK 16752762
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1
# define MOUSE_ROT_SPEED 0.05

/* OS Detection */
#ifdef __APPLE__
# define OS_MAC 1
#else
# define OS_LINUX 1
#endif

/* Keycodes for Mac */
#ifdef OS_MAC
# define KEY_W          13
# define KEY_A          0
# define KEY_S          1
# define KEY_D          2
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_ESC        53
#endif

/* Keycodes for Linux */
#ifdef OS_LINUX
# define KEY_W          119
# define KEY_A           97
# define KEY_S          115
# define KEY_D          100
# define KEY_LEFT       65361
# define KEY_RIGHT      65363
# define KEY_ESC        65307
#endif

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_dmap
{
        char    **brut_file;
}       t_dmap;

typedef struct s_img
{
	int             bpp;
	int             line_length;
	int             endian;
	int             width;
	int             height;
	void    *image;
	char    *addr;
}       t_img;

typedef struct s_textures
{
	char    *path_no;
	char    *path_so;
	char    *path_we;
	char    *path_ea;
	t_img   img_no;
	t_img   img_so;
	t_img   img_we;
	t_img   img_ea;
	int		color_c[3];
	int		color_f[3];
}       t_textures;

typedef struct s_ray
{
        double  camera;
        double  dir_x;
        double  dir_y;
        double  delta_dist_x;
        double  delta_dist_y;
        int             step_x;
        int             step_y;
        int             hit;
        int             side;
        double  side_dist_x;
        double  side_dist_y;
        int             map_x;
        int             map_y;
        int             draw_start;
        int             draw_end;
        double          perp_dist;
	int             line_height;
}	t_ray;

typedef struct s_data
{
        void    *mlx;
        void    *win;
        int             win_width;
        int             win_height;
        int             pixel_size_x;
        int             pixel_size_y;
        int             pixel_size;
        t_img   img;
        t_img   minimap_img;
}                               t_data;

typedef struct s_player
{
        double  pos_x;
        double  pos_y;
        int             color;
        double  dir_x;
        double  dir_y;
        double  fov_x;
        double  fov_y;
        double  mouse_x;
        char    orientation;
}                               t_player;

typedef struct s_game
{
        t_dmap          dmap;
        t_textures      textures;
        char            **map;
        int                     height;
        int                     width;
        int                     state;
        t_data          data;
        t_player        player;
}                               t_game;

int             destroy_display(t_game *game, char *str, int error);
int             close_game(t_game *game);
void    create_map(t_game *game);
void    init_values(t_game *game);
void    free_double_ptr(char **table);
int             ft_min(int i, int j);
void    create_minimap(t_game *game);
void    render_images(t_game *game);
void    draw_minimap_background(t_game *game, int scale, int center);
void    my_mlx_pixel_put(t_game *game, int x, int y, int color);
void    move_player(t_game *game, double dx, double dy);
void    rotate_player(t_game *game, int direction, double rot_speed);
void    apply_movement(t_game *game, int keycode);
int             handle_keypress(int keycode, t_game *game);
int             handle_mouse_move(int x, int y, t_game *game);
void	load_textures(t_game *game);
unsigned int	get_texture_pixel(t_game *game, t_img *tex, int x, int y);

/* PARSING */
int             init_data(t_game *game, char *cub_name);
int             extract_raw(t_game *game);
int             extract_textures(t_game *game, char *line, int type);
int             extract_colors(t_game *game, char *line, int type);
int             fill_map(int lines, t_game *game, char **brut_map);
void    find_player_position(t_game *game, int line_index);
void    raycasting(t_game *game);
int             check_walls_1(t_game *game);
int             check_walls_2(t_game *game);
int             check_char(char **map);
char    *skip_spaces(char *line);
int     is_line_empty(char *line);


/* GNL */
char    *get_next_line(int fd);

/* UTILS */
void    free_tab(char **tab);

#endif

