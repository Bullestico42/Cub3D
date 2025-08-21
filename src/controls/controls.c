/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:28:23 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/19 15:13:16 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controls.h"

#if defined(__APPLE__)

static void	center_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_move(game->data.win, cx, cy);
}

#else

static void	center_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
}

#endif

void	rotate_player(t_game *game, int direction, double rot_speed)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

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

int	handle_keypress(int keycode, t_game *game)
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
	else if (keycode == KEY_M)
	{
		if (!game->minimap_switch)
			game->minimap_switch = 1;
		else
			game->minimap_switch = 0;
	}
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
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

int	game_loop(t_game *game)
{
	double	delta;

	delta = 0.0;
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
	if (game->mouse_locked && game->mouse_dx_acc != 0.0)
	{
		delta = game->mouse_dx_acc * MOUSE_ROT_SPEED;
		if (delta < 0)
				rotate_player(game, -1, -delta);
		else
			rotate_player(game, 1, delta);
		game->mouse_dx_acc = 0.0;
	}
	return (enemy_update(game, 1.0 / 60.0), raycasting(game), render_images(game), 0);
}
