/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:37:11 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/04 14:30:16 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
			return ;
		}
		j++;
	}
}

int	ft_min(int i, int j)
{
	if (i < j)
		return (i);
	return (j);
}
void	free_double_ptr(char **table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
	table = NULL;
}
