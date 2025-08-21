/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 23:48:46 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 23:58:07 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	in_frame_e(t_img *f, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= f->width || y >= f->height)
		return (0);
	return (1);
}

unsigned int	texel_e(t_img_e *t, int x, int y)
{
	char	*src;
	int		off;

	if (x < 0 || y < 0 || x >= t->w || y >= t->h)
		return (ENEMY_COLOR_KEY);
	off = y * t->line_len + x * (t->bpp / 8);
	src = t->addr + off;
	return (*(unsigned int *)src);
}
