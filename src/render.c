/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/17 21:14:22 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->data.img.addr
		+ (y * game->data.img.line_length)
		+ (x * (game->data.img.bpp / 8));
	*(unsigned int *)dst = color;
}

/* ft_abs retourne la valeur absolue d'un nombre */
double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	set_deltas(t_game *game, t_ray *ray, int x)
{
	ray->camera = 2 * x / (double)game->data.win_width - 1;
	ray->dir_x = game->player.dir_x + game->player.fov_x * ray->camera;
	ray->dir_y = game->player.dir_y + game->player.fov_y * ray->camera;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = ft_abs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = ft_abs(1 / ray->dir_y);
}

void	set_directions(t_player *player, t_ray *r)
{
	r->map_x = (int)player->pos_x;
	r->map_y = (int)player->pos_y;
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (player->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - player->pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (player->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - player->pos_y) * r->delta_dist_y;
	}
}

void	ft_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->width
			|| ray->map_y < 0 || ray->map_y >= game->height)
		{
			ray->hit = 1;
			break ;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_params(t_game *game, t_ray *ray)
{
	double	perp_dist;
	int		line_height;

	if (ray->side == 0)
		perp_dist = (ray->map_x - game->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		perp_dist = (ray->map_y - game->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (perp_dist <= 0.001)
		perp_dist = 0.001;
	line_height = (int)(game->data.win_height / perp_dist);
	if (line_height > game->data.win_height * 2)
		line_height = game->data.win_height * 2;
	ray->draw_start = -line_height / 2 + game->data.win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + game->data.win_height / 2;
	if (ray->draw_end >= game->data.win_height)
		ray->draw_end = game->data.win_height - 1;
}

int	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->width
		|| map_y < 0 || map_y >= game->height)
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_forward(t_game *game)
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

void	move_backward(t_game *game)
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

void	move_left(t_game *game)
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

void	move_right(t_game *game)
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

void	rotate_player(t_game *game, int direction, double rot_speed)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	if (direction == -1)
		angle = -rot_speed;
	else
		angle = rot_speed;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.fov_x;
	game->player.dir_x = game->player.dir_x
		* cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.fov_x = game->player.fov_x
		* cos(angle) - game->player.fov_y * sin(angle);
	game->player.fov_y = old_plane_x * sin(angle)
		+ game->player.fov_y * cos(angle);
}

void	apply_movement(t_game *game, int keycode)
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
		rotate_player(game, -1, 0.1);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, 1, 0.1);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		destroy_display(game, "Exit\n", 0);
	apply_movement(game, keycode);
	raycasting(game);
	render_images(game);
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	double	mouse_x;
	double	deltas;

	(void)y;
	mouse_x = (double)x;
	deltas = mouse_x - game->player.mouse_x;
	if (deltas < 0)
		rotate_player(game, -1, 0.05);
	if (deltas > 0)
		rotate_player(game, 1, 0.05);
	raycasting(game);
	render_images(game);
	game->player.mouse_x = mouse_x;
	return (0);
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < game->data.win_width)
	{
		set_deltas(game, &ray, x);
		set_directions(&game->player, &ray);
		ft_dda(game, &ray);
		calculate_wall_params(game, &ray);
		y = 0;
		while (y < ray.draw_start)
			my_mlx_pixel_put(game, x, y++, 6579400);
		if (ray.side)
			color = 6579300 / 2;
		else
			color = 6579300;
		y = ray.draw_start;
		while (y <= ray.draw_end)
			my_mlx_pixel_put(game, x, y++, color);
		y = ray.draw_end + 1;
		while (y < game->data.win_height)
			my_mlx_pixel_put(game, x, y++, 6579250);
	}
}

void	draw_minimap_background(t_game *game, int scale, int center)
{
	int	i;
	int	j;
	int	offset;
	int	map_tile_x;
	int	map_tile_y;

	i = 0;
	while (i < game->data.win_width / 5)
	{
		j = 0;
		while (j < game->data.win_width / 5)
		{
			map_tile_x = game->player.pos_x + (i - center) / scale;
			map_tile_y = game->player.pos_y + (j - center) / scale;
			offset = j * game->data.minimap_img.line_length + i
				* (game->data.minimap_img.bpp / 8);
			if (map_tile_x >= 0 && map_tile_x < game->width &&
				map_tile_y >= 0 && map_tile_y < game->height)
			{
				if (game->map[map_tile_y][map_tile_x] == '1')
					*(unsigned int *)(game->data.minimap_img.addr + offset) = PINK;
				else
					*(unsigned int *)(game->data.minimap_img.addr + offset) = LAVENDER;
			}
			else
				*(unsigned int *)(game->data.minimap_img.addr + offset) = GREEN;
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, int center)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	offset;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			x = center - 2 + i;
			y = center - 2 + j;
			offset = y * game->data.minimap_img.line_length
				+ x * (game->data.minimap_img.bpp / 8);
			*(unsigned int *)(game->data.minimap_img.addr + offset) = BLUE;
			j++;
		}
		i++;
	}
}

void	draw_direction_line(t_game *game, int dir_x, int dir_y)
{
	int	thick_i;
	int	thick_j;
	int	offset;

	thick_i = -2;
	while (thick_i <= 1)
	{
		thick_j = -2;
		while (thick_j <= 1)
		{
			if ((dir_x + thick_i) >= 0
				&& (dir_x + thick_i) < game->data.win_width / 5
				&& (dir_y + thick_j) >= 0
				&& (dir_y + thick_j) < game->data.win_width / 5)
			{
				offset = (dir_y + thick_j) * game->data.minimap_img.line_length
					+ (dir_x + thick_i) * (game->data.minimap_img.bpp / 8);
				*(unsigned int *)(game->data.minimap_img.addr + offset) = BLUE;
			}
			thick_j++;
		}
		thick_i++;
	}
}

void	direction_line(t_game *game, int center)
{
	int	step;
	int	dir_x;
	int	dir_y;
	int	line_length;

	step = 1;
	line_length = 10;
	while (step <= line_length)
	{
		dir_x = center + 2 + (int)(game->player.dir_x * step);
		dir_y = center + 2 + (int)(game->player.dir_y * step);
		if (dir_x >= 0 && dir_x < game->data.win_width / 5
			&& dir_y >= 0 && dir_y < game->data.win_width / 5)
			draw_direction_line(game, dir_x, dir_y);
		step++;
	}
}

void	create_minimap(t_game *game)
{
	int	scale;
	int	center;

	scale = game->data.win_width / 5 / 10;
	center = game->data.win_width / 5 / 2;
	draw_minimap_background(game, scale, center);
	draw_player(game, center);
	direction_line(game, center);
}

void	create_new_image(t_game *game, t_img *img, int width, int height)
{
	img->image = mlx_new_image(game->data.mlx, width, height);
	if (!img->image)
		destroy_display(game, "Error\nCan't create image\n", 1);
	img->addr = mlx_get_data_addr(img->image,
			&img->bpp, &img->line_length, &img->endian);
}

void	render_images(t_game *game)
{
	mlx_put_image_to_window(
		game->data.mlx,
		game->data.win,
		game->data.img.image,
		0,
		0);
	create_minimap(game);
	mlx_put_image_to_window(
		game->data.mlx,
		game->data.win,
		game->data.minimap_img.image,
		0,
		0);
}

void	create_map(t_game *game)
{
	create_new_image(game, &game->data.img,
		game->data.win_width, game->data.win_height);
	raycasting(game);
	create_new_image(game, &game->data.minimap_img,
		game->data.win_width / 5, game->data.win_width / 5);
	render_images(game);
	mlx_hook(game->data.win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->data.win, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->data.win, 17, 0, close_game, game);
}
