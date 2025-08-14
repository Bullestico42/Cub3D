/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

static int  in_frame(t_img *f, int x, int y)
{
    if (x < 0 || y < 0)
        return (0);
    if (x >= f->width || y >= f->height)
        return (0);
    return (1);
}

static void put_px(t_img *f, int x, int y, unsigned int c)
{
    char    *dst;
    int     off;

    if (!in_frame(f, x, y))
        return ;
    off = y * f->line_length + x * (f->bpp / 8);
    dst = f->addr + off;
    *(unsigned int *)dst = c;
}

static unsigned int texel_c(t_img_c *t, int x, int y)
{
    char    *src;
    int     off;

    if (x < 0 || y < 0 || x >= t->w || y >= t->h)
        return (COIN_COLOR_KEY);
    off = y * t->line_len + x * (t->bpp / 8);
    src = t->addr + off;
    return (*(unsigned int *)src);
}

static int  screen_x_from_cam(int sw, double tx, double ty, int *sprite_h)
{
    int h;

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

void    coins_draw(t_game *g, double *zbuf)
{
    double  inv;
    double  tx;
    double  ty;
    int     scx;
    int     h;
    int     x;
    int     y;
    int     ds;
    int     de;
    int     i;

    if (!g->coins.tex.img)
        return ;
    i = 0;
    while (i < g->coins.count)
    {
        if (!g->coins.arr[i].collected)
        {
            inv = 1.0 / (g->player.fov_x * g->player.dir_y - g->player.dir_x
                    * g->player.fov_y);
            tx = inv * (g->player.dir_y * (g->coins.arr[i].x - g->player.pos_x)
                    - g->player.dir_x * (g->coins.arr[i].y - g->player.pos_y));
            ty = inv * (-g->player.fov_y * (g->coins.arr[i].x - g->player.pos_x)
                    + g->player.fov_x * (g->coins.arr[i].y - g->player.pos_y));
            scx = screen_x_from_cam(g->data.win_width, tx, ty, &h);
            if (scx >= -999999999 && ty > 1e-6)
            {
                ds = g->data.win_height / 2 - h / 2;
                de = g->data.win_height / 2 + h / 2;
                x = scx - h / 2;
                while (x <= scx + h / 2)
                {
                    if (x >= 0 && x < g->data.win_width && ty < zbuf[x])
                    {
                        int txx = (int)((double)(x - (scx - h / 2)) * g->coins.tex.w
                                / (double)h);
                        y = (ds < 0) ? 0 : ds;
                        while (y <= ((de >= g->data.win_height) ? g->data.win_height - 1 : de))
                        {
                            int tyy = (int)((double)(y - ds) * g->coins.tex.h / (double)h);
                            unsigned int c = texel_c(&g->coins.tex, txx, tyy);
                            if ((c & 0x00FFFFFF) != COIN_COLOR_KEY)
                                put_px(&g->data.img, x, y, c);
                            y++;
                        }
                    }
                    x++;
                }
            }
        }
        i++;
    }
}

