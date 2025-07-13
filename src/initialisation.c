/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:45:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/13 09:09:29 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_mlx(t_game *game)
{
	int	pixel_size_x;
	int	pixel_size_y;

	game->data.mlx = NULL;
	game->data.win = NULL;
	game->data.win_width = 900;
	game->data.win_height = 600;
	pixel_size_x = game->data.win_width / game->dmap.width;
	pixel_size_y = game->data.win_height / game->dmap.height;
	game->data.pixel_size = ft_min(pixel_size_x, pixel_size_y);
}

void	init_player(t_game *game)
{
	game->player.color = 6749952;
	if (game->player.orientation == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (game->player.orientation == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (game->player.orientation == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (game->player.orientation == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
	game->player.fov_x = 0.66;
	game->player.fov_y = 0;
}

/* Fonction servant initialiser les valeurs dans les différentes structurees. */
void	init_values(t_game *game)
{
	game->dmap.brut_file = NULL;
	init_player(game);
	init_mlx(game);
}
