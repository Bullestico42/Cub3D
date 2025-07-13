/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/13 10:21:45 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

/* Prototypes */
void    raycasting(t_game *game);
void    draw_player(t_game *game);
int     handle_keypress(int keycode, t_game *game);

static void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    dst = game->data.img.addr
        + (y * game->data.img.line_length)
        + (x * (game->data.img.bpp / 8));
    *(unsigned int *)dst = color;
}

/* ft_abs retourne la valeur absolue d'un nombre */
double    ft_abs(double i)
{
    return (i < 0 ? -i : i);
}

void    set_deltas(t_game *game, t_ray *ray, int x)
{
    ray->camera = 2 * x / (double)game->data.win_width - 1;
    ray->dir_x = game->player.dir_x + game->player.fov_x * ray->camera;
    ray->dir_y = game->player.dir_y + game->player.fov_y * ray->camera;
    ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : ft_abs(1 / ray->dir_x);
    ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : ft_abs(1 / ray->dir_y);
}

void    set_directions(t_game *game, t_ray *ray)
{
    ray->map_x = (int)game->player.pos_x;
    ray->map_y = (int)game->player.pos_y;
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
    }
}

void    ft_dda(t_game *game, t_ray *ray)
{
    ray->hit = 0;
    while (!ray->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x     += ray->step_x;
            ray->side       = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y       += ray->step_y;
            ray->side         = 1;
        }
        /* Si hors carte, on considère un hit pour arrêter la DDA */
        if (ray->map_x < 0 || ray->map_x >= game->dmap.width
            || ray->map_y < 0 || ray->map_y >= game->dmap.height)
        {
            ray->hit = 1;
            break;
        }
        /* Collision mur */
        if (game->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

static int can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->dmap.width ||
		map_y < 0 || map_y >= game->dmap.height)
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

static void move_forward(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

static void move_backward(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = game->player.pos_x - game->player.dir_x * move_speed;
	new_y = game->player.pos_y - game->player.dir_y * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

static void move_left(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = game->player.pos_x + game->player.dir_y * move_speed;
	new_y = game->player.pos_y - game->player.dir_x * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

static void move_right(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.1;
	new_x = game->player.pos_x - game->player.dir_y * move_speed;
	new_y = game->player.pos_y + game->player.dir_x * move_speed;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

static void rotate_player(t_game *game, int direction)
{
	double	rot_speed;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.1;
	if (direction == -1)
		angle = -rot_speed;
	else
		angle = rot_speed;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.fov_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.fov_x = game->player.fov_x * cos(angle) - game->player.fov_y * sin(angle);
	game->player.fov_y = old_plane_x * sin(angle) + game->player.fov_y * cos(angle);
}

static void apply_movement(t_game *game, int keycode)
{
	if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -1);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, 1);
}

int    handle_keypress(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
    if (keycode == KEY_ESC)
        destroy_display(game, "Exit\n", 0);
    apply_movement(game, keycode);
    raycasting(game);
    draw_player(game);
    mlx_put_image_to_window(
        game->data.mlx,
        game->data.win,
        game->data.img.image,
        0,
        0);
    return (0);
}

void    raycasting(t_game *game)
{
    t_ray    ray;
    int      x;
    double   perp_dist;
    int      line_height;
    int      draw_start;
    int      draw_end;
    int      y;
    int      color;

    x = 0;
    while (x < game->data.win_width)
    {
        set_deltas(game, &ray, x);
        set_directions(game, &ray);
        ft_dda(game, &ray);
        /* distance perpendiculaire */
        if (ray.side == 0)
            perp_dist = (ray.map_x - game->player.pos_x +
                (1 - ray.step_x) / 2) / ray.dir_x;
        else
            perp_dist = (ray.map_y - game->player.pos_y +
                (1 - ray.step_y) / 2) / ray.dir_y;
        line_height = (int)(game->data.win_height / perp_dist);
        draw_start = -line_height / 2 + game->data.win_height / 2;
        if (draw_start < 0) draw_start = 0;
        draw_end = line_height / 2 + game->data.win_height / 2;
        if (draw_end >= game->data.win_height) draw_end = game->data.win_height - 1;
        /* plafond */
        for (y = 0; y < draw_start; y++)
            my_mlx_pixel_put(game, x, y, 6579400);
        /* mur */
        color = (ray.side) ? 6579300 / 2 : 6579300;
        for (y = draw_start; y <= draw_end; y++)
            my_mlx_pixel_put(game, x, y, color);
        /* sol */
        for (y = draw_end + 1; y < game->data.win_height; y++)
            my_mlx_pixel_put(game, x, y, 6579250);
        x++;
    }
}

void    draw_player(t_game *game)
{
    int    i;
    int    j;
    int    x;
    int    y;
    int    offset;

    i = -2;
    while (i < 2)
    {
        j = -2;
        while (j < 2)
        {
            x = (int)(game->player.pos_x * game->data.pixel_size) + i;
            y = (int)(game->player.pos_y * game->data.pixel_size) + j;
            offset = y * game->data.img.line_length
                   + x * (game->data.img.bpp / 8);
            *(unsigned int *)(game->data.img.addr + offset) = game->player.color;
            j++;
        }
        i++;
    }
}

void    create_map(t_game *game)
{
    game->data.img.image = mlx_new_image(
        game->data.mlx,
        game->data.win_width,
        game->data.win_height);
    if (!game->data.img.image)
        destroy_display(game, "Error\nCan't create image\n", 1);
    game->data.img.addr = mlx_get_data_addr(
        game->data.img.image,
        &game->data.img.bpp,
        &game->data.img.line_length,
        &game->data.img.endian);
    raycasting(game);
    draw_player(game);
    mlx_put_image_to_window(
        game->data.mlx,
        game->data.win,
        game->data.img.image,
        0,
        0);
    mlx_hook(game->data.win, 2, 1L << 0, handle_keypress, game);
    mlx_hook(game->data.win, 17, 0, destroy_display, game);
}
