/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:26:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/21 15:23:18 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "../../headers/cub3d.h"

typedef struct s_game	t_game;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_img	t_img;

typedef struct s_tex
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
}		t_tex;

void			create_map(t_game *game);
int				ft_min(int i, int j);
void			create_minimap(t_game *game);
void			render_images(t_game *game);
void			draw_minimap_background(t_game *game, float scale, int center);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			rotate_player(t_game *game, int direction, double rot_speed);
void			load_textures(t_game *game);
unsigned int	get_texture_pixel(t_game *game, t_img *tex, int x, int y);
int				rgb_to_hex(int r, int g, int b);
void			set_directions(t_player *player, t_ray *r);
void			ft_dda(t_game *game, t_ray *ray);
void			calculate_wall_params(t_game *game, t_ray *ray);
void			set_deltas(t_game *game, t_ray *ray, int x);
void			draw_wall(t_game *game, t_ray *ray, int x);
void			colors_and_background(t_game *game, int colors[2]);
void			init_tex(t_game *game, t_ray *ray, t_img **tex, t_tex *t);

#endif