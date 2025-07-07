/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 20:39:21 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_min(int i, int j)
{
	if (i < j)
		return (i);
	return (j);
}

void	draw_player(t_game *game)
{
	int		i = -2;
	int		j;
	int		bpp;
	int		line_length;
	int		endian;
	int		offset;
	int		color = 16711680;
	int		map_width = 34;
	int		map_heigth = 14;
	int		pixel_size_x = game->data.win_width / map_width;
	int		pixel_size_y = game->data.win_heigth / map_heigth;
	int		pixel_size = ft_min(pixel_size_x, pixel_size_y);
	game->player.pos_x = 29.5;
	game->player.pos_y = 4.5;
	int px = (int)(game->player.pos_x * pixel_size);
	int py = (int)(game->player.pos_y * pixel_size);
	void	*image = mlx_new_image(game->data.mlx, game->data.win_width, game->data.win_heigth);
	if (!image)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	char	*addr = mlx_get_data_addr(image, &bpp, &line_length, &endian);
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			int x = px + i;
			int y = py + j;
			offset = y * line_length + x * (bpp / 8);
			*(unsigned int *)(addr + offset) = color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->data.mlx, game->data.win, image, 0, 0);
}

/*Initialise la structure de la map en lisant le fichier avec get_next_line.
Chaque ligne lue est stockée dans un tableau de string.*/
void	create_map(t_game *game, char *map_path)
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
		game->map.lines[i] = ft_calloc(34, sizeof(char));
		if (!game->map.lines[i])
			destroy_display(game, "Error\nFile can't malloc map line\n", 1);
		game->map.lines[i] = get_next_line(game->map.fd);
		if (!game->map.lines[i])
			destroy_display(game, "Error\nCan't read map\n", 1);
		i++;
	}
	draw_player(game);
}