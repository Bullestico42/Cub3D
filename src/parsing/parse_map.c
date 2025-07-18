/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:44:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/18 22:08:28 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	fill_map(int lines, t_game *game, char **brut_map)
{
	int i;

	printf("\n\n");
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
		printf("%s", game->map[i]);
		i++;
	}
	printf("\n\n");
	game->map[i] = NULL;
	if (check_walls_1(game))
	{
		printf("ERROR WALLS\n");
		return (1);
	}
    return (0);
}

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

int	white_space(char c)
{
	if (c != ' ' && c != '\t' && c != '\r'
		&& c != '\n' && c != '\v' && c != '\f')
		return (0);
	return (1);
}

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

int	check_walls_2(t_game *game)
{
	int x;
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

int	check_char(char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (white_space(map[y][x]) || map[y][x] == '0' || map[y][x] == '1'
				|| map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'S' ||
					map[y][x] == 'W')
				x++;
			else
				return (1);
		}
		y++;
	}
	return (0);
}
