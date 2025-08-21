/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:44:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/19 15:34:42 by apiscopo         ###   ########.fr       */
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
		printf("Error: walls\n");
		return (1);
	}
	return (0);
}

// obtient uniquement la plus grande largeur de la map
static int	get_width(t_game *game)
{
	int	y;
	int	state;

	y = 0;
	state = 0;
	while (game->map[y])
	{
		state = ft_strlen(game->map[y]);
		if (state < 3)
			return (1);
		if (state > game->width)
			game->width = state;
		y++;
	}
	return (0);
}

// skip tout les white space
int	white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (0);
	return (1);
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
