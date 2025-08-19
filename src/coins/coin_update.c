/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:09:51 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 22:09:52 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

void	coins_update(t_game *g)
{
	int		i;
	double	dx;
	double	dy;

	if (!g || !g->coins.arr)
		return ;
	i = 0;
	while (i < g->coins.count)
	{
		if (!g->coins.arr[i].collected)
		{
			dx = g->player.pos_x - g->coins.arr[i].x;
			dy = g->player.pos_y - g->coins.arr[i].y;
			if (dx * dx + dy * dy < 0.25)
			{
				g->coins.arr[i].collected = 1;
				g->player.speed += 0.02;
			}
		}
		i++;
	}
}
