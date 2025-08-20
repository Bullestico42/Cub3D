/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:56 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/20 23:16:59 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"
#include "../headers/cub3d.h"

static int	is_wall_cell(t_game *g, int mx, int my)
{
	int		row_len;
	char	c;

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

static double	nearest_point(double point, double cell_min, double cell_max)
{
	if (point < cell_min)
		return (cell_min);
	if (point > cell_max)
		return (cell_max);
	return (point);
}

static void	push_from_cell(t_enemy *e, int mx, int my)
{
	double	nx;
	double	ny;
	double	dx;
	double	dy;
	double	d;

	nx = nearest_point(e->x, (double)mx, (double)mx + 1.0);
	ny = nearest_point(e->y, (double)my, (double)my + 1.0);
	dx = e->x - nx;
	dy = e->y - ny;
	d = sqrt(dx * dx + dy * dy);
	if (e->radius - d > 0.0)
	{
		if (d < 1e-12)
			d = 1.0;
		e->x += dx / d * (e->radius - d);
		e->y += dy / d * (e->radius - d);
	}
}

void	enemy_resolve_collision(t_game *g)
{
	int	cx;
	int	cy;
	int	j;
	int	i;

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
