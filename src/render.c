/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/09 02:33:47 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	set_deltas(t_game *game, t_ray *ray, int x)
{
	(*ray).camera = 2 * x / (double)game->data.win_width - 1;
	(*ray).ray_dir_x = game->player.dir_x + game->player.fov_x * (*ray).camera;
	(*ray).ray_dir_y = game->player.dir_y + game->player.fov_y * (*ray).camera;
	if ((*ray).ray_dir_x == 0)
		(*ray).delta_dist_x = 1e30;
	else
		(*ray).delta_dist_x = ft_abs(1 / (*ray).ray_dir_x);
	if ((*ray).ray_dir_y == 0)
		(*ray).delta_dist_y = 1e30;
	else
		(*ray).delta_dist_y = ft_abs(1 / (*ray).ray_dir_y);
}

void	set_directions(t_game *game, t_ray *ray)
{
	(*ray).map_x = (int)game->player.pos_x;
	(*ray).map_y = (int)game->player.pos_y;
	if ((*ray).ray_dir_x < 0)
	{
		(*ray).step_x = -1;
		(*ray).side_dist_x = (game->player.pos_x - (*ray).map_x) * (*ray).delta_dist_x;
	}
	else
	{
		(*ray).step_x = 1;
		(*ray).side_dist_x = ((*ray).map_x + 1.0 - game->player.pos_x) * (*ray).delta_dist_x;
	}
	if ((*ray).ray_dir_y < 0)
	{
		(*ray).step_y = -1;
		(*ray).side_dist_y = (game->player.pos_y - (*ray).map_y) * (*ray).delta_dist_y;
	}
	else
	{
		(*ray).step_y = 1;
		(*ray).side_dist_y = ((*ray).map_y + 1.0 - game->player.pos_y) * (*ray).delta_dist_y;
	}
}

void	draw_rays(t_game *game, t_ray *ray)
{
	double	ray_pos_x;
	double	ray_pos_y;
	int		px;
	int		py;
	int		offset;

	ray_pos_x = game->player.pos_x;
	ray_pos_y = game->player.pos_y;
	while (game->map.lines[(int)ray_pos_y][(int)ray_pos_x] != '1')
	{
		px = ray_pos_x * game->data.pixel_size;
		py = ray_pos_y * game->data.pixel_size;
		offset = py * game->data.img.line_length + px * (game->data.img.bpp / 8);
		*(unsigned int *)(game->data.img.addr + offset) = 16711680;
		ray_pos_x += (*ray).ray_dir_x * 0.05;
		ray_pos_y += (*ray).ray_dir_y * 0.05;
	}
}

void	ft_dda(t_game *game, t_ray *ray)
{
	(*ray).hit = 0;
	while ((*ray).hit == 0)
	{
		if ((*ray).side_dist_x < (*ray).side_dist_y)
		{
			(*ray).side_dist_x += (*ray).delta_dist_x;
			(*ray).map_x += (*ray).step_x;
			//(*ray).side = 0;
		}
		else
		{
			(*ray).side_dist_y += (*ray).delta_dist_y;
			(*ray).map_y += (*ray).step_y;
			//side = 1;
		}
		if (game->map.lines[(*ray).map_y][(*ray).map_x] == '1')
			(*ray).hit = 1;
	}
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->data.win_width)
	{
		set_deltas(game, &ray, x);
		set_directions(game, &ray);
		draw_rays(game, &ray);
		ft_dda(game, &ray);
		x++;
	}
}

void	draw_player(t_game *game)
{
	int		i;
	int		j;
	int		offset;
	int		x;
	int		y;

	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			x = (int)(game->player.pos_x * game->data.pixel_size) + i;
			y = (int)(game->player.pos_y * game->data.pixel_size) + j;
			offset = y * game->data.img.line_length + x * (game->data.img.bpp / 8);
			*(unsigned int *)(game->data.img.addr + offset) = game->player.color;
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	game->data.img.image = mlx_new_image(game->data.mlx, game->data.win_width, game->data.win_heigth);
	if (!game->data.img.image)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	game->data.img.addr = mlx_get_data_addr(game->data.img.image, &game->data.img.bpp, &game->data.img.line_length, &game->data.img.endian);
	raycasting(game);
	draw_player(game);
	mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img.image, 0, 0);
}

/*Initialise la structure de la map en lisant le fichier avec get_next_line.
Chaque ligne lue est stockée dans un tableau de string.*/
void	read_map(t_game *game, char *map_path)
{
	int	i;

	i = 0;
	game->map.fd = open(map_path, O_RDONLY);
	if (game->map.fd == -1)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	game->map.lines = ft_calloc(15, sizeof(char *));
	if (!game->map.lines)
		destroy_display(game, "Error\nFile can't malloc map\n", 1);
	while (i < 14)
	{
		game->map.lines[i] = get_next_line(game->map.fd);
		if (!game->map.lines[i])
			destroy_display(game, "Error\nCan't read map\n", 1);
		i++;
	}
}

void	create_map(t_game *game, char *map_path)
{
	read_map(game, map_path);
	draw_map(game);
}
