/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:11:03 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/28 15:47:11 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int	is_line_empty(char *line)
{
	line = skip_spaces(line);
	if (*line == '\0' || *line == '\n')
		return (1);
	return (0);
}

//Verifie qu'il n'ait qu un seul player
static int	check_player(char c, int *state)
{
	if (c == 'E' || c == 'N' || c == 'S' || c == 'W')
		*(state) += 1;
	if (*(state) > 1)
		return (0);
	else
		return (1);
}

// vérifie s'il n y a pas de char inconnu
int	check_char(char **map)
{
	int	y;
	int	x;
	int	state;

	y = 0;
	x = 0;
	state = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((white_space(map[y][x]) || map[y][x] == '0' || map[y][x] == '1'
			|| map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'S'
			|| map[y][x] == 'W') && (check_player(map[y][x], &state)))
				x++;
			else
				return (1);
		}
		y++;
	}
	if (state == 0)
		return (1);
	return (0);
}
