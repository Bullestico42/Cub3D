/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/19 15:34:30 by apiscopo         ###   ########.fr       */
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

// vérifie s'il n y a pas de char inconnu
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
			if (white_space(map[y][x]) || map[y][x] == '0'
			|| map[y][x] == '1' || map[y][x] == 'E' || map[y][x] == 'N'
			|| map[y][x] == 'S' || map[y][x] == 'W')
				x++;
			else
				return (1);
		}
		y++;
	}
	return (0);
}
