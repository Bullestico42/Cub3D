/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:40 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/27 17:55:30 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	set_minimap_pixel(t_game *game, int offset, int x, int y)
{
	unsigned int	color;

	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		if (game->map[y][x] != '0' && game->map[y][x] != 'E'
			&& game->map[y][x] != 'W' && game->map[y][x] != 'N'
			&& game->map[y][x] != 'S')
			color = 00000000;
		else
			color = GRAY;
	}
	else
		color = 00000000;
	*(unsigned int *)(game->data.minimap_img.addr + offset) = color;
}

void	draw_minimap_background(t_game *game, float scale, int center)
{
	int		i;
	int		j;
	int		offset;
	float	world_x;
	float	world_y;

	i = 0;
	while (i < game->data.win_width / 5)
	{
		j = 0;
		while (j < game->data.win_width / 5)
		{
			world_x = game->player.pos_x + (i - center) / scale;
			world_y = game->player.pos_y + (j - center) / scale;
			offset = j * game->data.minimap_img.line_length
				+ i * (game->data.minimap_img.bpp / 8);
			set_minimap_pixel(game, offset, (int)world_x, (int)world_y);
			j++;
		}
		i++;
	}
}
