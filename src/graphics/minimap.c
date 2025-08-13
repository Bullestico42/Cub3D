/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:11 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/13 15:15:31 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_player(t_game *game, int center)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	offset;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			x = center - 4 + i;
			y = center - 4 + j;
			if (x >= 0 && x < game->data.win_width / 5
				&& y >= 0 && y < game->data.win_width / 5)
			{
				offset = y * game->data.minimap_img.line_length
					+ x * (game->data.minimap_img.bpp / 8);
				*(unsigned int *)(game->data.minimap_img.addr + offset) = BLUE;
			}
			j++;
		}
		i++;
	}
}

static void	plot_dir_thick(t_game *game, int x, int y)
{
	int	dx;
	int	dy;
	int	offset;

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

void	direction_line(t_game *game, int center)
{
	int	step;
	int	line_length;
	int	dir_x;
	int	dir_y;

	step = 1;
	line_length = 15;
	while (step <= line_length)
	{
		dir_x = center + (int)(game->player.dir_x * step);
		dir_y = center + (int)(game->player.dir_y * step);
		plot_dir_thick(game, dir_x, dir_y);
		step++;
	}
}

void	create_minimap(t_game *game)
{
	float	scale;
	int		center;
	int		minimap_size;

	minimap_size = game->data.win_width / 5;
	center = minimap_size / 2;
	scale = minimap_size / 12.0f;
	draw_minimap_background(game, scale, center);
	draw_player(game, center);
	direction_line(game, center);
}
