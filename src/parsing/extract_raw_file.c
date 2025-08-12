/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_raw_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/12 18:57:13 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	extract_map(t_game *game, int start)
{
	int	height;

	height = 0;
	while (game->parsing.brut_file[start + height])
		height++;
	if (height < 3)
		return (printf("Error: Map Invalid\n"), 1);
	if (fill_map(height, game, &game->parsing.brut_file[start]))
		return (1);
	return (0);
}

static int	finalize_map(t_game *game, int i)
{
	while (game->parsing.brut_file[i]
		&& is_line_empty(game->parsing.brut_file[i]))
		i++;
	if (game->parsing.tex != 15 || game->parsing.col != 3)
		return (printf("Error: Map Invalid\n"), 1);
	if (!game->parsing.brut_file[i])
		return (printf("Error: Map Invalid\n"), 1);
	if (extract_map(game, i))
		return (1);
	free_double_ptr(game->parsing.brut_file);
	return (0);
}

int	extract_raw(t_game *game)
{
	int	index;

	game->parsing.tex = 0;
	game->parsing.col = 0;
	index = parse_elements(game);
	if (index < 0)
		return (printf("Error: Map Invalid\n"), 1);
	return (finalize_map(game, index));
}
