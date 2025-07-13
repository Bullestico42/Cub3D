/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:44:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/13 08:55:12 by dimatayi         ###   ########.fr       */
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
    return (0);
}

void	find_player_position(t_game *game, int line_index)
{
	int	j;

	j = 0;
	while (game->map[line_index][j])
	{
		if (game->map[line_index][j] == 'N' || game->map[line_index][j] == 'S' ||
			game->map[line_index][j] == 'E' || game->map[line_index][j] == 'W')
		{
			game->player.pos_x = j + 0.5;
			game->player.pos_y = line_index + 0.5;
			game->player.orientation = game->map[line_index][j];
			return;
		}
		j++;
	}
}
