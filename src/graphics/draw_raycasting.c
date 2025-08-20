/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:24:19 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/21 00:29:43 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_background(t_game *game, int colors[2])
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->data.win_height / 2)
	{
		x = -1;
		while (++x < game->data.win_width)
			my_mlx_pixel_put(game, x, y, colors[0]);
	}
	while (y < game->data.win_height)
	{
		x = -1;
		while (++x < game->data.win_width)
			my_mlx_pixel_put(game, x, y, colors[1]);
		y++;
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	t_img			*tex;
	t_tex			t;
	int				y;
	unsigned int	color;

	init_tex(game, ray, &tex, &t);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		t.tex_y = (int)t.tex_pos % tex->height;
		if (t.tex_y < 0)
			t.tex_y += tex->height * 5;
		t.tex_pos += t.step;
		color = get_texture_pixel(game, tex, t.tex_x, t.tex_y);
		my_mlx_pixel_put(game, x, y++, color);
	}
}

void	colors_and_background(t_game *game, int colors[2])
{
	colors[0] = rgb_to_hex(game->textures.color_c[0],
			game->textures.color_c[1], game->textures.color_c[2]);
	colors[1] = rgb_to_hex(game->textures.color_f[0],
			game->textures.color_f[1], game->textures.color_f[2]);
	draw_background(game, colors);
}
