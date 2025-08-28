/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:33:18 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/27 15:40:41 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

#if defined(__APPLE__)

static void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide();
	mlx_mouse_move(game->data.win, cx, cy);
}

void	center_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_move(game->data.win, cx, cy);
}

#else

void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide(game->data.mlx, game->data.win);
	mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
}

void	center_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
}

#endif

void	lock_mouse(t_game *game)
{
	int	cx;
	int	cy;

	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	hide_and_move_mouse(game, cx, cy);
	game->mouse_locked = 1;
}
