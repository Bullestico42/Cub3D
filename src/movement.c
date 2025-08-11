/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:03 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/11 14:48:58 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
    }
}

