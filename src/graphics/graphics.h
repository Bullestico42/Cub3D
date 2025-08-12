/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:26:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/12 16:30:24 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "../../headers/cub3d.h"

void			create_map(t_game *game);
int				ft_min(int i, int j);
void			create_minimap(t_game *game);
void			render_images(t_game *game);
void			draw_minimap_background(t_game *game, int scale, int center);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			rotate_player(t_game *game, int direction, double rot_speed);
void			load_textures(t_game *game);
unsigned int	get_texture_pixel(t_game *game, t_img *tex, int x, int y);
int				rgb_to_hex(int r, int g, int b);

#endif