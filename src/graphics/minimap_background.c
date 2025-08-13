/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:40 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/13 15:20:04 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	set_minimap_pixel(t_game *game, int offset, int x, int y)
{
	unsigned int	color;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= game->width)
		x = game->width - 1;
	if (y >= game->height)
		y = game->height - 1;
	if (game->map[y][x] == '1')
		color = PINK;
	else
		color = LAVENDER;
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
