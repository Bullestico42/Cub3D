/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by ChatGPT          ###   ########.fr       */
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
                g->player.speed += 0.2;
            }
        }
        i++;
    }
}

