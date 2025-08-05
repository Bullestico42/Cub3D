/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/18 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

static int  can_move_to(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    map_x = (int)x;
    map_y = (int)y;
    if (map_x < 0 || map_x >= game->width
        || map_y < 0 || map_y >= game->height)
        return (0);
    if (game->map[map_y][map_x] == '1')
        return (0);
    return (1);
}

static void    teleport_player_if_needed(t_game *game)
{
    char    cell;
    t_portal    *in_p;
    t_portal    *out_p;
    t_vec       new_pos;
    double      angle;
    double      new_dir;
    double      dx;
    double      dy;

    cell = game->map[(int)game->player.pos_y][(int)game->player.pos_x];
    if (cell != '2' && cell != '3')
        return ;
    in_p = get_portal_by_id(game, cell - '0');
    dx = game->player.pos_x - in_p->pos.x;
    dy = game->player.pos_y - in_p->pos.y;
    if (dx * dx + dy * dy > PORTAL_RADIUS * PORTAL_RADIUS)
        return ;
    out_p = get_portal_by_id(game, cell == '2' ? 3 : 2);
    angle = atan2(game->player.dir_y, game->player.dir_x);
    transform_through_portal((t_vec){game->player.pos_x, game->player.pos_y},
            angle, *in_p, *out_p, &new_pos, &new_dir);
    game->player.pos_x = new_pos.x;
    game->player.pos_y = new_pos.y;
    game->player.dir_x = cos(new_dir);
    game->player.dir_y = sin(new_dir);
}

void    move_player(t_game *game, double dx, double dy)
{
    double  new_x;
    double  new_y;

    new_x = game->player.pos_x + dx * MOVE_SPEED;
    new_y = game->player.pos_y + dy * MOVE_SPEED;
    if (can_move_to(game, new_x, new_y))
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
        teleport_player_if_needed(game);
    }
}

