/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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

/*
** Apply the portal transformation to a hit position and direction.
** The hit position is expressed in world coordinates; it is converted
** to the local space of the entry portal, rotated into the exit
** portal's space and translated back to world coordinates.
*/
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

void    init_portals(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '2')
            {
                game->portals[0].pos.x = x + 0.5;
                game->portals[0].pos.y = y + 0.5;
                game->portals[0].angle = 0;
                game->portals[0].id = 2;
            }
            if (game->map[y][x] == '3')
            {
                game->portals[1].pos.x = x + 0.5;
                game->portals[1].pos.y = y + 0.5;
                game->portals[1].angle = 0;
                game->portals[1].id = 3;
            }
            x++;
        }
        y++;
    }
}

/*
** Return the portal matching the given id or NULL if not found.
*/
t_portal   *get_portal_by_id(t_game *game, int id)
{
    if (game->portals[0].id == id)
        return (&game->portals[0]);
    if (game->portals[1].id == id)
        return (&game->portals[1]);
    return (NULL);
}

void    cast_ray(t_game *game, t_ray *ray)
{
    t_player    p;
    double      total_dist;
    double      dist;
    int         depth;
    char        cell;
    t_vec       new_pos;
    double      new_dir;

    p = game->player;
    p.dir_x = ray->dir_x;
    p.dir_y = ray->dir_y;
    total_dist = 0.0;
    depth = 0;
    while (depth < MAX_PORTAL_DEPTH)
    {
        set_directions(&p, ray);
        ft_dda(game, ray);
        if (ray->side == 0)
            dist = ray->side_dist_x - ray->delta_dist_x;
        else
            dist = ray->side_dist_y - ray->delta_dist_y;
        total_dist += dist;
        ray->wall_hit_x = p.pos_x + dist * ray->dir_x;
        ray->wall_hit_y = p.pos_y + dist * ray->dir_y;
        if (ray->map_x < 0 || ray->map_x >= game->width
            || ray->map_y < 0 || ray->map_y >= game->height)
            break ;
        cell = game->map[ray->map_y][ray->map_x];
        if (cell == '2' || cell == '3')
        {
            t_portal    *in_p;
            t_portal    *out_p;
            double      dx;
            double      dy;
            int         id;

            id = cell - '0';
            in_p = get_portal_by_id(game, id);
            dx = ray->wall_hit_x - in_p->pos.x;
            dy = ray->wall_hit_y - in_p->pos.y;
            if (dx * dx + dy * dy <= PORTAL_RADIUS * PORTAL_RADIUS)
            {
                out_p = get_portal_by_id(game, id == 2 ? 3 : 2);
                transform_through_portal((t_vec){ray->wall_hit_x, ray->wall_hit_y},
                        atan2(ray->dir_y, ray->dir_x),
                        *in_p, *out_p, &new_pos, &new_dir);
                p.pos_x = new_pos.x;
                p.pos_y = new_pos.y;
                ray->dir_x = cos(new_dir);
                ray->dir_y = sin(new_dir);
                ray->delta_dist_x = ray->dir_x == 0 ? 1e30 : fabs(1 / ray->dir_x);
                ray->delta_dist_y = ray->dir_y == 0 ? 1e30 : fabs(1 / ray->dir_y);
                depth++;
                continue ;
            }
        }
        break ;
    }
    ray->perp_dist = total_dist;
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

