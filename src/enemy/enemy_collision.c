/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:56 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/14 16:15:09 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static int      is_wall_cell(t_game *g, int mx, int my)
{
    int     row_len;
    char    c;

    if (mx < 0 || my < 0 || my >= g->height)
        return (1);
    row_len = ft_strlen(g->map[my]);
    if (mx >= row_len)
        return (1);
    c = g->map[my][mx];
    if (c == '1' || c == ' ')
        return (1);
    return (0);
}

static void     push_from_cell(t_enemy *e, int mx, int my)
{
    double  nx;
    double  ny;
    double  dx;
    double  dy;
    double  d;
    double  need;

    nx = e->x;
    if (nx < (double)mx)
        nx = (double)mx;
    if (nx > (double)mx + 1.0)
        nx = (double)mx + 1.0;
    ny = e->y;
    if (ny < (double)my)
        ny = (double)my;
    if (ny > (double)my + 1.0)
        ny = (double)my + 1.0;
    dx = e->x - nx;
    dy = e->y - ny;
    d = sqrt(dx * dx + dy * dy);
    need = e->radius - d;
    if (need > 0.0)
    {
        if (d < 1e-12)
            d = 1.0;
        e->x += dx / d * need;
        e->y += dy / d * need;
    }
}

void    enemy_resolve_collision(t_game *g)
{
    int     cx;
    int     cy;
    int     j;
    int     i;

    cx = (int)floor(g->enemy.x);
    cy = (int)floor(g->enemy.y);
    j = -1;
    while (++j <= 1)
    {
        i = -1;
        while (++i <= 1)
            if (is_wall_cell(g, cx + i, cy + j))
                push_from_cell(&g->enemy, cx + i, cy + j);
    }
}
