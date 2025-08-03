/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/18 00:00:00 by ChatGPT          ###   ########.fr       */
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

void    apply_movement(t_game *game, int keycode)
{
    if (keycode == KEY_W)
        move_player(game, game->player.dir_x, game->player.dir_y);
    else if (keycode == KEY_S)
        move_player(game, -game->player.dir_x, -game->player.dir_y);
    else if (keycode == KEY_A)
        move_player(game, game->player.dir_y, -game->player.dir_x);
    else if (keycode == KEY_D)
        move_player(game, -game->player.dir_y, game->player.dir_x);
    else if (keycode == KEY_LEFT)
        rotate_player(game, -1, ROT_SPEED);
    else if (keycode == KEY_RIGHT)
        rotate_player(game, 1, ROT_SPEED);
}

int     handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        destroy_display(game, "Exit\n", 0);
    apply_movement(game, keycode);
    raycasting(game);
    render_images(game);
    return (0);
}

int     handle_mouse_move(int x, int y, t_game *game)
{
    double  mouse_x;
    double  deltas;

    (void)y;
    mouse_x = (double)x;
    deltas = mouse_x - game->player.mouse_x;
    if (deltas < 0)
        rotate_player(game, -1, MOUSE_ROT_SPEED);
    if (deltas > 0)
        rotate_player(game, 1, MOUSE_ROT_SPEED);
    raycasting(game);
    render_images(game);
    game->player.mouse_x = mouse_x;
    return (0);
}

