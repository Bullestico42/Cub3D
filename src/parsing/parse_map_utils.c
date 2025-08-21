/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:35:25 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/21 00:37:12 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

// obtient uniquement la plus grande largeur de la map
int	get_width(t_game *game)
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
