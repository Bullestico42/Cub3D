/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/06 16:57:02 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

typedef struct s_tex
{
    double  wall_x;
    int     tex_x;
    double  step;
    double  tex_pos;
    int     tex_y;
}       t_tex;

void    set_deltas(t_game *game, t_ray *ray, int x);
void    set_directions(t_player *player, t_ray *r);
void    ft_dda(t_game *game, t_ray *ray);
void    calculate_wall_params(t_game *game, t_ray *ray);
static void     set_wall_hit(t_game *game, t_ray *ray);

static t_img    *select_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
    {
        if (ray->dir_x > 0)
            return (&game->textures.img_ea);
        return (&game->textures.img_we);
    }
    if (ray->dir_y > 0)
        return (&game->textures.img_so);
    return (&game->textures.img_no);
}

static void draw_background(t_game *game, int colors[2])
{
    int x;
    int y;

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

static void     set_wall_hit(t_game *game, t_ray *ray)
{
    if (ray->side == 0)
    {
        ray->wall_hit_x = ray->map_x;
        ray->wall_hit_y = game->player.pos_y + ray->perp_dist * ray->dir_y;
    }
    else
    {
        ray->wall_hit_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
        ray->wall_hit_y = ray->map_y;
    }
}

static void init_tex(t_game *game, t_ray *ray, t_img **tex, t_tex *t)
{
    *tex = select_texture(game, ray);
    if (ray->side == 0)
        t->wall_x = ray->wall_hit_y;
    else
        t->wall_x = ray->wall_hit_x;
    t->wall_x -= floor(t->wall_x);
    t->tex_x = (int)(t->wall_x * (*tex)->width);
    if (ray->side == 0 && ray->dir_x > 0)
        t->tex_x = (*tex)->width - t->tex_x - 1;
    if (ray->side == 1 && ray->dir_y < 0)
        t->tex_x = (*tex)->width - t->tex_x - 1;
    t->step = 1.0 * (*tex)->height / ray->line_height;
    t->tex_pos = (ray->draw_start - game->data.win_height / 2.0
            + ray->line_height / 2.0) * t->step;
}

static void draw_wall(t_game *game, t_ray *ray, int x)
{
    t_img           *tex;
    t_tex           t;
    int             y;
    unsigned int    color;

    init_tex(game, ray, &tex, &t);
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        t.tex_y = (int)t.tex_pos & (tex->height - 1);
        t.tex_pos += t.step;
        color = get_texture_pixel(game, tex, t.tex_x, t.tex_y);
        my_mlx_pixel_put(game, x, y++, color);
    }
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
    draw_background(game, colors);
    x = -1;
    while (++x < game->data.win_width)
    {
        set_deltas(game, &ray, x);
        set_directions(&game->player, &ray);
        ft_dda(game, &ray);
        calculate_wall_params(game, &ray);
        set_wall_hit(game, &ray);
        draw_wall(game, &ray, x);
    }
}

