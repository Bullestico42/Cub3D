/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:29:03 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/19 15:34:37 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	handle_tex(t_game *game, char *line, int idx)
{
	int	mask;

	mask = 1 << idx;
	if ((game->parsing.tex & mask) || !extract_textures(game, line, idx))
		return (-1);
	game->parsing.tex |= mask;
	return (1);
}

static int	parse_texture_line(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (handle_tex(game, line, 0));
	if (!ft_strncmp(line, "SO", 2))
		return (handle_tex(game, line, 1));
	if (!ft_strncmp(line, "WE", 2))
		return (handle_tex(game, line, 2));
	if (!ft_strncmp(line, "EA", 2))
		return (handle_tex(game, line, 3));
	return (0);
}

static int	parse_color_line(t_game *game, char *line)
{
	if (line[0] == 'F')
	{
		if (game->parsing.col & 1 || !extract_colors(game, line, 0))
			return (-1);
		game->parsing.col |= 1;
	}
	else if (line[0] == 'C')
	{
		if (game->parsing.col & 2 || !extract_colors(game, line, 1))
			return (-1);
		game->parsing.col |= 2;
	}
	else
		return (0);
	return (1);
}

static int	parse_element(t_game *game, char *line)
{
	int	state;

	state = parse_texture_line(game, line);
	if (state == -1)
		return (1);
	if (state == 1)
		return (0);
	state = parse_color_line(game, line);
	if (state == -1)
		return (1);
	if (state == 1)
		return (0);
	return (1);
}

int	parse_elements(t_game *game)
{
	int	i;

	i = 0;
	while (game->parsing.brut_file[i])
	{
		if (is_line_empty(game->parsing.brut_file[i]))
		{
			i++;
			continue ;
		}
		if (game->parsing.tex == 15 && game->parsing.col == 3)
			break ;
		if (parse_element(game, skip_spaces(game->parsing.brut_file[i])))
			return (-1);
		i++;
	}
	return (i);
}
