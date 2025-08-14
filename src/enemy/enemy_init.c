/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:12:03 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/14 19:21:58 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

int	enemy_init(t_enemy *e, double x, double y, double speed, double radius)
{
	if (!e)
		return (-1);
	e->x = x;
	e->y = y;
	e->vx = 0.0;
	e->vy = 0.0;
	e->speed = speed;
	e->radius = radius;
	e->alive = 1;
	e->tex.img = 0;
	e->tex.addr = 0;
	e->tex.bpp = 0;
	e->tex.line_len = 0;
	e->tex.endian = 0;
	e->tex.w = 0;
	e->tex.h = 0;
	return (0);
}
