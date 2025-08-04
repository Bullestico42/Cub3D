/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/04 21:20:10 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

void    set_directions(t_player *player, t_ray *r);
void    ft_dda(t_game *game, t_ray *ray);
void    calculate_wall_params(t_game *game, t_ray *ray);

static int  rgb_to_hex(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

void    set_deltas(t_game *game, t_ray *ray, int x)
{
    ray->camera = 2 * x / (double)game->data.win_width - 1;
    ray->dir_x = game->player.dir_x + game->player.fov_x * ray->camera;
    ray->dir_y = game->player.dir_y + game->player.fov_y * ray->camera;
    ray->delta_dist_x = ray->dir_x == 0 ? 1e30 : fabs(1 / ray->dir_x);
    ray->delta_dist_y = ray->dir_y == 0 ? 1e30 : fabs(1 / ray->dir_y);
}

static t_img	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->textures.img_we);
		return (&game->textures.img_ea);
	}
	if (ray->dir_y > 0)
		return (&game->textures.img_no);
	return (&game->textures.img_so);
}

static void	draw_column(t_game *game, t_ray *ray, int x, int colors[2])
{
    int             y;
	t_img           *tex;
	double          wall_x;
	int             tex_x;
	double          step;
	double          tex_pos;
	int             tex_y;
	unsigned int    color;

	y = 0;
	while (y < ray->draw_start)
		my_mlx_pixel_put(game, x, y++, colors[0]);
	tex = select_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - game->data.win_height / 2.0
			+ ray->line_height / 2.0) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = *(unsigned int *)(tex->addr + tex_y * tex->line_length
				+ tex_x * (tex->bpp / 8));
		my_mlx_pixel_put(game, x, y++, color);
	}
	while (y < game->data.win_height)
		my_mlx_pixel_put(game, x, y++, colors[1]);
}

void    raycasting(t_game *game)
{
    t_ray   ray;
    int     x;
    int     colors[2];

    colors[0] = rgb_to_hex(game->textures.color_c[0],
            game->textures.color_c[1], game->textures.color_c[2]);
    colors[1] = rgb_to_hex(game->textures.color_f[0],
            game->textures.color_f[1], game->textures.color_f[2]);
    x = -1;
    while (++x < game->data.win_width)
    {
        set_deltas(game, &ray, x);
        set_directions(&game->player, &ray);
        ft_dda(game, &ray);
        calculate_wall_params(game, &ray);
        draw_column(game, &ray, x, colors);
    }
}

