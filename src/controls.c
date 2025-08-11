/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:23 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/11 16:05:07 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

void    rotate_player(t_game *game, int direction, double rot_speed)
{
	double  angle;
	double  old_dir_x;
	double  old_plane_x;

	angle = rot_speed;
	if (direction == -1)
		angle = -rot_speed;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.fov_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.fov_x = game->player.fov_x * cos(angle)
		- game->player.fov_y * sin(angle);
	game->player.fov_y = old_plane_x * sin(angle)
		+ game->player.fov_y * cos(angle);
}

int     handle_mouse_move(int x, int y, t_game *game)
{
	double  mouse_x;
	double  deltas;
	int		cx;
	int		cy;

	if (!game || !game->mouse_locked)
        return (0);
	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	(void)y;
	mouse_x = (double)x;
	deltas = mouse_x - game->player.mouse_x;
    if (abs(x - cx) <= MOUSE_CENTER_EPS && abs(y - cy) <= MOUSE_CENTER_EPS)
        return (0);
	else if (deltas < 0)
		rotate_player(game, -1, MOUSE_ROT_SPEED);
	else if (deltas > 0)
		rotate_player(game, 1, MOUSE_ROT_SPEED);
	game->player.mouse_x = mouse_x;
# if defined(__APPLE__)
    mlx_mouse_move(game->data.win, cx, cy);
# else
    mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
	printf("mousecentered\n");
# endif
	return (0);
}

int     handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		destroy_display(game, "EXIT\n", 0);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int     handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int     game_loop(t_game *game)
{
    if (game->keys.w)
        move_player(game, game->player.dir_x, game->player.dir_y);
    if (game->keys.s)
        move_player(game, -game->player.dir_x, -game->player.dir_y);
    if (game->keys.a)
        move_player(game, game->player.dir_y, -game->player.dir_x);
    if (game->keys.d)
        move_player(game, -game->player.dir_y, game->player.dir_x);
    if (game->keys.left)
        rotate_player(game, -1, ROT_SPEED);
    if (game->keys.right)
        rotate_player(game, 1, ROT_SPEED);
    raycasting(game);
    render_images(game);
    return (0);
}