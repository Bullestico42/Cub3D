/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:40 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/11 14:49:00 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static void set_minimap_pixel(t_game *game, int offset, int x, int y)
{
    unsigned int    color;

    if (x >= 0 && x < game->width && y >= 0 && y < game->height)
    {
        if (game->map[y][x] == '1')
            color = PINK;
        else
            color = LAVENDER;
    }
    else
        color = GREEN;
    *(unsigned int *)(game->data.minimap_img.addr + offset) = color;
}

void    draw_minimap_background(t_game *game, int scale, int center)
{
    int i;
    int j;
    int offset;
    int tile_x;
    int tile_y;

    i = 0;
    while (i < game->data.win_width / 5)
    {
        j = 0;
        while (j < game->data.win_width / 5)
        {
            tile_x = game->player.pos_x + (i - center) / scale;
            tile_y = game->player.pos_y + (j - center) / scale;
            offset = j * game->data.minimap_img.line_length
                + i * (game->data.minimap_img.bpp / 8);
            set_minimap_pixel(game, offset, tile_x, tile_y);
            j++;
        }
        i++;
    }
}

