/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/19 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

void    set_directions(t_player *player, t_ray *r)
{
    r->map_x = (int)player->pos_x;
    r->map_y = (int)player->pos_y;
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (player->pos_x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - player->pos_x) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (player->pos_y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - player->pos_y) * r->delta_dist_y;
    }
}

void    ft_dda(t_game *game, t_ray *ray)
{
    ray->hit = 0;
    while (!ray->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_x < 0 || ray->map_x >= game->width
            || ray->map_y < 0 || ray->map_y >= game->height)
            ray->hit = 1;
        else if (game->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void    calculate_wall_params(t_game *game, t_ray *ray)
{
    double  perp_dist;
    int     line_height;

    if (ray->side == 0)
        perp_dist = (ray->map_x - game->player.pos_x
                + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        perp_dist = (ray->map_y - game->player.pos_y
                + (1 - ray->step_y) / 2) / ray->dir_y;
    if (perp_dist <= 0.001)
        perp_dist = 0.001;
    line_height = (int)(game->data.win_height / perp_dist);
    if (line_height > game->data.win_height * 2)
        line_height = game->data.win_height * 2;
    ray->draw_start = -line_height / 2 + game->data.win_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = line_height / 2 + game->data.win_height / 2;
    if (ray->draw_end >= game->data.win_height)
        ray->draw_end = game->data.win_height - 1;
}

