/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 00:00:00 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 22:30:08 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

static int	screen_x_from_cam(int sw, double tx, double ty, int *sprite_h)
{
	int	h;

	if (ty <= 1e-6)
		return (-1000000000);
	h = (int)fabs((double)sw * 0.75 / ty);
	if (h < 8)
		h = 8;
	if (h > sw)
		h = sw;
	*sprite_h = h;
	return ((int)((sw / 2.0) * (1.0 + tx / ty)));
}

void	coin_to_camera(t_game *g, int i, double *tx, double *ty)
{
	double	inv;
	double	dx;
	double	dy;

	dx = g->coins.arr[i].x - g->player.pos_x;
	dy = g->coins.arr[i].y - g->player.pos_y;
	inv = 1.0 / (g->player.fov_x * g->player.dir_y - g->player.dir_x
			* g->player.fov_y);
	*tx = inv * (g->player.dir_y * dx - g->player.dir_x * dy);
	*ty = inv * (-g->player.fov_y * dx + g->player.fov_x * dy);
}

void	coin_image(t_game *g, double *zbuf, double tx, double ty)
{
	int	scx;
	int	h;
	int	x;

	scx = screen_x_from_cam(g->data.win_width, tx, ty, &h);
	if (scx >= -999999999 && ty > 1e-6)
	{
		x = scx - h / 2;
		while (x <= scx + h / 2)
		{
			if (x >= 0 && x < g->data.win_width && ty < zbuf[x])
				draw_coin_column(g, x, scx, h);
			x++;
		}
	}
}
