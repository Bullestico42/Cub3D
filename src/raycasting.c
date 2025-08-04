/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/04 14:02:28 by bullestico       ###   ########.fr       */
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

static void draw_column(t_game *game, t_ray *ray, int x, int colors[2])
{
    int y;
    int color;

    y = 0;
    while (y < ray->draw_start)
        my_mlx_pixel_put(game, x, y++, colors[0]);
    color = ray->side ? 6579300 / 2 : 6579300;
    y = ray->draw_start;
    while (y <= ray->draw_end)
        my_mlx_pixel_put(game, x, y++, color);
    y = ray->draw_end + 1;
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

