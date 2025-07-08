/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:44:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/08 03:27:58 by bullestico       ###   ########.fr       */
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
			return (free_tab(game->map), 1);
        printf("%s", game->map[i]);
		i++;
	}
	printf("\n\n");
	game->map[i] = NULL;
    return (0);
}