/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:44:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/28 15:42:50 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

// rempli un tableau possedant la map
int	fill_map(int lines, t_game *game, char **brut_map)
{
	int	i;

	game->height = lines;
	game->map = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!game->map)
		return (0);
	i = 0;
	while (i < lines)
	{
		game->map[i] = ft_strdup(brut_map[i]);
		if (!game->map[i])
			return (free_double_ptr(game->map), 1);
		find_player_position(game, i);
		i++;
	}
	game->map[i] = NULL;
	if (check_walls_1(game))
	{
		printf("Error: Map parsing\n");
		return (1);
	}
	return (0);
}

// vérifie la premiere est derniere ligne de la map
int	check_walls_1(t_game *game)
{
	int	x;

	x = 0;
	if (get_width(game))
		return (1);
	game->height -= 1;
	while (game->map[0][x] && game->map[game->height][x])
	{
		if ((game->map[0][x] == '1' || white_space(game->map[0][x]))
			&& (game->map[game->height][x] == '1' ||
				white_space(game->map[game->height][x])))
			x++;
		else
			return (1);
	}
	if (check_walls_2(game))
		return (1);
	return (0);
}

// vérifie la gauche et droite de la map
int	check_walls_2(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (game->map[y])
	{
		if (game->map[y][x] == '1' &&
			game->map[y][(ft_strlen(game->map[y])) - 2] == '1')
		{
			y++;
			x = 0;
		}
		else if (white_space(game->map[y][x]))
			x++;
		else
			return (1);
	}
	if (check_char(game->map))
		return (1);
	return (0);
}
