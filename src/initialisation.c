/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:45:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 22:19:15 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_mlx(t_game *game)
{
	int	pixel_size_x;
	int	pixel_size_y;

	game->data.mlx = NULL;
	game->data.win = NULL;
	game->data.win_width = 800;
	game->data.win_heigth = 600;
	pixel_size_x = game->data.win_width / game->map.width;
	pixel_size_y = game->data.win_heigth / game->map.heigth;
	game->data.pixel_size = ft_min(pixel_size_x, pixel_size_y);
}

/* Fonction servant initialiser les valeurs dans la structure game et ses sous-structurees. */
void	init_values(t_game *game)
{
	game->player.pos_x = 29.5;
	game->player.pos_y = 4.5;
	game->map.width = 34;
	game->map.heigth = 14;
	game->map.lines = NULL;
	game->player.color = 16711680;
	init_mlx(game);
}
