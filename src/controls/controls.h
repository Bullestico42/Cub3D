/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:35:27 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/20 22:34:36 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H
# include "../../headers/cub3d.h"

int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		game_loop(t_game *game);
void	move_player(t_game *game, double dx, double dy);
void	apply_movement(t_game *game, int keycode);
int		handle_mouse_move(int x, int y, t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	lock_mouse(t_game *game);
void	center_mouse(t_game *game, int cx, int cy);

#endif