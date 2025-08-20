/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:43:39 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 22:45:44 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controls.h"

static int	check_mouse_centered(int x, int y, t_game *game)
{
	int	cx;
	int	cy;

	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	if (abs(x - cx) <= MOUSE_CENTER_EPS && abs(y - cy) <= MOUSE_CENTER_EPS)
		return (1);
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	int	cx;
	int	cy;

	if (!game || !game->mouse_locked)
		return (0);
	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	if (check_mouse_centered(x, y, game))
		return (0);
	game->mouse_dx_acc += (x - cx);
	center_mouse(game, cx, cy);
	return (0);
}
