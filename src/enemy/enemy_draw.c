/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:16:18 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/21 00:27:52 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	put_px(t_img *f, int x, int y, unsigned int c)
{
	char	*dst;
	int		off;

	if (!in_frame_e(f, x, y))
		return ;
	off = y * f->line_length + x * (f->bpp / 8);
	dst = f->addr + off;
	*(unsigned int *)dst = c;
}

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

void	enemy_to_camera(t_game *g, double *tx, double *ty)
{
	double	inv;

	inv = 1.0 / (g->player.fov_x * g->player.dir_y - g->player.dir_x
			* g->player.fov_y);
	*tx = inv * (g->player.dir_y * (g->enemy.x - g->player.pos_x)
			- g->player.dir_x * (g->enemy.y - g->player.pos_y));
	*ty = inv * (-g->player.fov_y * (g->enemy.x - g->player.pos_x)
			+ g->player.fov_x * (g->enemy.y - g->player.pos_y));
}

void	draw_enemy_column(t_game *g, int x, int scx, int h)
{
	int				y;
	int				de;
	int				ds;
	int				txx;
	unsigned int	c;

	ds = g->data.win_height / 2 - h / 2;
	de = g->data.win_height / 2 + h / 2;
	txx = (int)((double)(x - (scx - h / 2)) *g->enemy.tex.w / (double)h);
	if (ds < 0)
		y = 0;
	else
		y = ds;
	if (de >= g->data.win_height)
		de = g->data.win_height - 1;
	while (y <= de)
	{
		c = texel_e(&g->enemy.tex, txx,
				(int)((double)(y - ds) *g->enemy.tex.h / (double)h));
		if ((c & 0x00FFFFFF) != ENEMY_COLOR_KEY)
			put_px(&g->data.img, x, y, c);
		y++;
	}
}

void	enemy_draw(t_game *g, double *zbuf)
{
	double	tx;
	double	ty;
	int		scx;
	int		h;
	int		x;

	if (!g->enemy.alive || !g->enemy.tex.img)
		return ;
	enemy_to_camera(g, &tx, &ty);
	scx = screen_x_from_cam(g->data.win_width, tx, ty, &h);
	if (scx < -999999999 || ty <= 1e-6)
		return ;
	x = scx - h / 2;
	while (x <= scx + h / 2)
	{
		if (x >= 0 && x < g->data.win_width && ty < zbuf[x])
			draw_enemy_column(g, x, scx, h);
		x++;
	}
}
