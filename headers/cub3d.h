/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/13 11:04:42 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 42

/* OS Detection */
#ifdef __APPLE__
# define OS_MAC 1
#else
# define OS_LINUX 1
#endif

/* Keycodes for Mac */
#ifdef OS_MAC
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_ESC	53
#endif

/* Keycodes for Linux */
#ifdef OS_LINUX
# define KEY_W		119
# define KEY_A		 97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307
#endif

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_dmap
{
	int		height;
	int		width;
	char	**brut_file;
}	t_dmap;

typedef struct s_textures
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	void	*t_no;
	void	*t_so;
	void	*t_we;
	void	*t_ea;
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
}				t_ray;

typedef struct s_img
{
	int		bpp;
	int		line_length;
	int		endian;
	void	*image;
	char	*addr;
}				t_img;


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
}				t_data;

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
}				t_player;

typedef struct s_game
{
	t_dmap		dmap;
	t_textures	textures;
	char		**map;
	int			state;
	t_data		data;
	t_player	player;
}				t_game;

int		destroy_display(t_game *game, char *str, int error);
void	create_map(t_game *game);
void	init_values(t_game *game);
void	free_double_ptr(char **table);
int		ft_min(int i, int j);

//PARSING
int		init_data(t_game *game, char *cub_name);
int		extract_raw(t_game *game);
int		extract_textures(t_game *game, int name, int is_okay);
int		extract_colors(t_game *game, int i, char name);
int		fill_map(int lines, t_game *game, char **brut_map);
void	find_player_position(t_game *game, int line_index);
void	raycasting(t_game *game);
void	draw_player(t_game *game);
int		handle_keypress(int keycode, t_game *game);

//GNL
char	*get_next_line(int fd);

//UTILS
void	free_tab(char **tab);

#endif