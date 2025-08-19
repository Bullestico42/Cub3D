/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/19 23:09:01 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

static int	in_frame(t_img *f, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= f->width || y >= f->height)
		return (0);
	return (1);
}

static void	put_px(t_img *f, int x, int y, unsigned int c)
{
	char	*dst;
	int		off;

	if (!in_frame(f, x, y))
		return ;
	off = y * f->line_length + x * (f->bpp / 8);
	dst = f->addr + off;
	*(unsigned int *)dst = c;
}

static unsigned	int	texel_c(t_img_c *t, int x, int y)
{
	char	*src;
	int		off;

	if (x < 0 || y < 0 || x >= t->w || y >= t->h)
		return (COIN_COLOR_KEY);
	off = y * t->line_len + x * (t->bpp / 8);
	src = t->addr + off;
	return (*(unsigned int *)src);
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

void	draw_coin_column(t_game *g, int x, int scx, int h)
{
	int				y;
	int				ds;
	int				de;
	unsigned int	c;

	ds = g->data.win_height / 2 - h / 2;
	de = g->data.win_height / 2 + h / 2;
	if (ds < 0)
		y = 0;
	else
		y = ds;
	if (de >= g->data.win_height)
		de = g->data.win_height - 1;
	while (y <= de)
	{
		c = texel_c(&g->coins.tex,
				(int)((double)(x - (scx - h / 2)) *g->coins.tex.w / (double)h),
				(int)((double)(y - ds) *g->coins.tex.h / (double)h));
		if ((c & 0x00FFFFFF) != COIN_COLOR_KEY)
			put_px(&g->data.img, x, y, c);
		y++;
	}
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

void	coins_draw(t_game *g, double *zbuf)
{
	double	tx;
	double	ty;
	int		i;

	if (!g->coins.tex.img)
		return ;
	i = 0;
	while (i < g->coins.count)
	{
		if (!g->coins.arr[i].collected)
		{
			coin_to_camera(g, i, &tx, &ty);
			coin_image(g, zbuf, tx, ty);
		}
		i++;
	}
}
