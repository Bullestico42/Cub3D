/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/09 02:33:47 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_ray
{
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
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
}				t_ray;

typedef struct s_map
{
	int		fd;
	char	**lines;
	int		width;
	int		heigth;
}				t_map;

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
	int		win_heigth;
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
}				t_player;

typedef struct s_game
{
	t_data		data;
	t_map		map;
	t_player	player;
}				t_game;

int		destroy_display(t_game *game, char *str, int error);
void	create_map(t_game *game, char *map_path);
void	init_values(t_game *game);
void	free_double_ptr(char **table);
int		ft_min(int i, int j);
void	read_map(t_game *game, char *map_path);

#endif