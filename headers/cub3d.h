/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/12 19:22:35 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// PARSING
#include "../src/parsing/parsing.h"
// GRAPHICS
#include "../src/graphics/graphics.h"
// CONTROLS

#include "../src/controls/controls.h"
# define BLUE 6591981
# define LAVENDER 15792383
# define GREEN 9419919
# define GRAY 14474460
# define PINK 16752762
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02
# define MOUSE_ROT_SPEED 0.03
# define MOUSE_CENTER_EPS 0.3
# define FOV_K 0.66

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
# include "../mlx/mlx_mac/mlx.h"
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
# include "../mlx/mlx_linux/mlx.h"
#endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_parsing
{
	char	**brut_file;
	int		tex;
	int		col;
	int		value;
	int		index;
}	t_parsing;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_img
{
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	void	*image;
	char	*addr;
}	t_img;

typedef struct s_textures
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	t_img	img_no;
	t_img	img_so;
	t_img	img_we;
	t_img	img_ea;
	int		color_c[3];
	int		color_f[3];
}	t_textures;

typedef struct s_ray
{
	double	camera;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		draw_start;
	int		draw_end;
	double	perp_dist;
	int		line_height;
}	t_ray;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	int		pixel_size_x;
	int		pixel_size_y;
	int		pixel_size;
	t_img	img;
	t_img	minimap_img;
}	t_data;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		color;
	double	dir_x;
	double	dir_y;
	double	fov_x;
	double	fov_y;
	char	orientation;
}	t_player;

typedef struct s_game
{
	char		**map;
	int			height;
	int			width;
	int			state;
	int			mouse_locked;
	double		mouse_dx_acc;
	t_textures	textures;
	t_parsing	parsing;
	t_data		data;
	t_player	player;
	t_keys		keys;
}	t_game;

// UTILS
int		destroy_display(t_game *game, char *str, int error);
int		close_game(t_game *game);
void	init_values(t_game *game);
void	free_double(char **table);
void	free_tab(char **tab);

#endif
