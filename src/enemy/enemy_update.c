/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:15:24 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/14 16:15:47 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	seek_velocity(t_enemy *e, double px, double py, double dt)
{
	double	dx;
	double	dy;
	double	len;
	double	ax;
	double	ay;
	double	acc;

	dx = px - e->x;
	dy = py - e->y;
	len = sqrt(dx * dx + dy * dy);
	if (len > 1e-6)
	{
		dx /= len;
		dy /= len;
	}
	ax = dx * e->speed - e->vx;
	ay = dy * e->speed - e->vy;
	acc = 8.0;
	e->vx += ax * acc * dt;
	e->vy += ay * acc * dt;
}

void	enemy_update(t_game *g, double dt)
{
	if (!g->enemy.alive)
		return ;
	if (dt <= 0.0)
		dt = 1.0 / 60.0;
	seek_velocity(&g->enemy, g->player.pos_x, g->player.pos_y, dt);
	g->enemy.x += g->enemy.vx * dt;
	g->enemy.y += g->enemy.vy * dt;
	enemy_resolve_collision(g);
}