/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/08 01:58:26 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	while (x < game->data.win_width)
	{
		camera_x = 2 * x / (double)game->data.win_width - 1;
		ray_dir_x = game->player.dir_x + game->player.fov_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.fov_y * camera_x;
		x++;
	}
}

void	draw_map(t_game *game)
{
	int		i;
	int		j;
	int		offset;
	int		px;
	int		py;

	px = (int)(game->player.pos_x * game->data.pixel_size);
	py = (int)(game->player.pos_y * game->data.pixel_size);
	game->data.img.image = mlx_new_image(game->data.mlx, game->data.win_width, game->data.win_heigth);
	if (!game->data.img.image)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	game->data.img.addr = mlx_get_data_addr(game->data.img.image, &game->data.img.bpp, &game->data.img.line_length, &game->data.img.endian);
	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			int x = px + i;
			int y = py + j;
			offset = y * game->data.img.line_length + x * (game->data.img.bpp / 8);
			*(unsigned int *)(game->data.img.addr + offset) = game->player.color;
			j++;
		}
		i++;
	}
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

