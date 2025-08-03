/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/18 00:00:00 by ChatGPT          ###   ########.fr       */
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

