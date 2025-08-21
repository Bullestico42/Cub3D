/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:45:27 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 15:34:26 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_mlx(t_game *game)
{
	int	pixel_size_x;
	int	pixel_size_y;

	game->data.mlx = NULL;
	game->data.win = NULL;
	game->data.win_width = 1440;
	game->data.win_height = 900;
	pixel_size_x = game->data.win_width / game->width;
	pixel_size_y = game->data.win_height / game->height;
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
	game->player.fov_x = -game->player.dir_y * FOV_K;
	game->player.fov_y = game->player.dir_x * FOV_K;
	game->player.speed = MOVE_SPEED;
}

/* Fonction servant initialiser les valeurs dans les différentes structurees. */
void	init_values(t_game *game)
{
	game->parsing.brut_file = NULL;
	game->minimap_switch = 0;
	init_player(game);
	init_mlx(game);
	ft_memset(&game->keys, 0, sizeof(t_keys));
}
