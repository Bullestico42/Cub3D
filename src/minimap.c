/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/18 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void    draw_player(t_game *game, int center)
{
    int i;
    int j;
    int x;
    int y;
    int offset;

    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            x = center - 2 + i;
            y = center - 2 + j;
            offset = y * game->data.minimap_img.line_length
                + x * (game->data.minimap_img.bpp / 8);
            *(unsigned int *)(game->data.minimap_img.addr + offset) = BLUE;
            j++;
        }
        i++;
    }
}

static void plot_dir_thick(t_game *game, int x, int y)
{
    int dx;
    int dy;
    int offset;

    dx = -2;
    while (dx <= 1)
    {
        dy = -2;
        while (dy <= 1)
        {
            if (x + dx >= 0 && x + dx < game->data.win_width / 5
                && y + dy >= 0 && y + dy < game->data.win_width / 5)
            {
                offset = (y + dy) * game->data.minimap_img.line_length
                    + (x + dx) * (game->data.minimap_img.bpp / 8);
                *(unsigned int *)(game->data.minimap_img.addr + offset) = BLUE;
            }
            dy++;
        }
        dx++;
    }
}

void    direction_line(t_game *game, int center)
{
    int step;
    int line_length;
    int dir_x;
    int dir_y;

    step = 1;
    line_length = 10;
    while (step <= line_length)
    {
        dir_x = center + 2 + (int)(game->player.dir_x * step);
        dir_y = center + 2 + (int)(game->player.dir_y * step);
        plot_dir_thick(game, dir_x, dir_y);
        step++;
    }
}

void    create_minimap(t_game *game)
{
    int scale;
    int center;

    scale = game->data.win_width / 5 / 10;
    center = game->data.win_width / 5 / 2;
    draw_minimap_background(game, scale, center);
    draw_player(game, center);
    direction_line(game, center);
}

