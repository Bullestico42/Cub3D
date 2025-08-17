/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/15 22:56:53 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

void    coins_update(t_game *g)
{
    int     i;
    double  dx;
    double  dy;

    if (!g || !g->coins.arr)
        return ;
    i = 0;
    while (i < g->coins.count)
    {
        if (!g->coins.arr[i].collected)
        {
            dx = g->player.pos_x - g->coins.arr[i].x;
            dy = g->player.pos_y - g->coins.arr[i].y;
            if (dx * dx + dy * dy < 0.25)
            {
                g->coins.arr[i].collected = 1;
                g->player.speed += 0.02;
            }
        }
        i++;
    }
}

