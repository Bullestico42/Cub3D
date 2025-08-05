/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/05 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

#define MAX_PORTAL_DEPTH 5

void    set_directions(t_player *player, t_ray *r);
void    ft_dda(t_game *game, t_ray *ray);

static t_vec rotate(t_vec v, double angle)
{
    t_vec r;

    r.x = v.x * cos(angle) - v.y * sin(angle);
    r.y = v.x * sin(angle) + v.y * cos(angle);
    return (r);
}

void    transform_through_portal(t_vec hit_pos, double ray_dir,
            t_portal in, t_portal out, t_vec *new_pos, double *new_dir)
{
    t_vec offset;

    offset.x = hit_pos.x - in.pos.x;
    offset.y = hit_pos.y - in.pos.y;
    offset = rotate(offset, -in.angle);
    offset = rotate(offset, out.angle);
    new_pos->x = out.pos.x + offset.x;
    new_pos->y = out.pos.y + offset.y;
    *new_dir = ray_dir + (out.angle - in.angle);
}

static void set_portal(t_game *game, t_portal *p, int x, int y, int id)
{
    p->pos.x = x + 0.5;
    p->pos.y = y + 0.5;
    if (y > 0 && game->map[y - 1][x] != '1')
        p->angle = 0;
    else if (x + 1 < game->width && game->map[y][x + 1] != '1')
        p->angle = M_PI / 2;
    else if (y + 1 < game->height && game->map[y + 1][x] != '1')
        p->angle = M_PI;
    else
        p->angle = 3 * M_PI / 2;
    p->id = id;
}

void    init_portals(t_game *game)
{
    int y;
    int x;

    game->portals[0].id = 0;
    game->portals[1].id = 0;
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '2')
                set_portal(game, &game->portals[0], x, y, 2);
            if (game->map[y][x] == '3')
                set_portal(game, &game->portals[1], x, y, 3);
            x++;
        }
        y++;
    }
}

t_portal   *get_portal_by_id(t_game *game, int id)
{
    if (game->portals[0].id == id)
        return (&game->portals[0]);
    if (game->portals[1].id == id)
        return (&game->portals[1]);
    return (NULL);
}

static int portal_in_radius(t_portal *p, t_ray *ray)
{
    double dx;
    double dy;

    dx = ray->wall_hit_x - p->pos.x;
    dy = ray->wall_hit_y - p->pos.y;
    if (dx * dx + dy * dy > PORTAL_RADIUS * PORTAL_RADIUS)
        return (0);
    return (1);
}

static int teleport_ray(t_game *game, t_ray *ray, t_player *p,
            char cell, int *depth)
{
    t_portal    *in_p;
    t_portal    *out_p;
    t_vec       new_pos;
    double      new_dir;
    int         id;

    id = cell - '0';
    in_p = get_portal_by_id(game, id);
    if (!in_p || !portal_in_radius(in_p, ray))
        return (0);
    out_p = get_portal_by_id(game, id == 2 ? 3 : 2);
    if (!out_p)
        return (0);
    transform_through_portal((t_vec){ray->wall_hit_x, ray->wall_hit_y},
        atan2(ray->dir_y, ray->dir_x), *in_p, *out_p, &new_pos, &new_dir);
    p->pos_x = new_pos.x + cos(new_dir) * PORTAL_EPS;
    p->pos_y = new_pos.y + sin(new_dir) * PORTAL_EPS;
    ray->dir_x = cos(new_dir);
    ray->dir_y = sin(new_dir);
    ray->delta_dist_x = ray->dir_x == 0 ? 1e30 : fabs(1 / ray->dir_x);
    ray->delta_dist_y = ray->dir_y == 0 ? 1e30 : fabs(1 / ray->dir_y);
    (*depth)++;
    return (1);
}

static double step_dist(t_ray *ray)
{
    if (ray->side == 0)
        return (ray->side_dist_x - ray->delta_dist_x);
    return (ray->side_dist_y - ray->delta_dist_y);
}

static int out_of_bounds(t_game *game, t_ray *ray)
{
    if (ray->map_x < 0 || ray->map_x >= game->width
        || ray->map_y < 0 || ray->map_y >= game->height)
        return (1);
    return (0);
}

static void finalize_ray(t_game *game, t_ray *ray)
{
    if (ray->perp_dist <= 0.001)
        ray->perp_dist = 0.001;
    ray->line_height = (int)(game->data.win_height / ray->perp_dist);
    if (ray->line_height > game->data.win_height * 2)
        ray->line_height = game->data.win_height * 2;
    ray->draw_start = -ray->line_height / 2 + game->data.win_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + game->data.win_height / 2;
    if (ray->draw_end >= game->data.win_height)
        ray->draw_end = game->data.win_height - 1;
}

void    cast_ray(t_game *game, t_ray *ray)
{
    t_player    p;
    int         depth;

    p = game->player;
    ray->perp_dist = 0.0;
    depth = 0;
    while (depth < MAX_PORTAL_DEPTH)
    {
        char    cell;

        set_directions(&p, ray);
        ft_dda(game, ray);
        ray->perp_dist += step_dist(ray);
        ray->wall_hit_x = p.pos_x + step_dist(ray) * ray->dir_x;
        ray->wall_hit_y = p.pos_y + step_dist(ray) * ray->dir_y;
        if (out_of_bounds(game, ray))
            break ;
        cell = game->map[ray->map_y][ray->map_x];
        if ((cell == '2' || cell == '3')
            && teleport_ray(game, ray, &p, cell, &depth))
            continue ;
        break ;
    }
    finalize_ray(game, ray);
}

