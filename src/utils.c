/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:37:11 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 02:27:36 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/* Fonction servant initialiser les valeurs dans la structure game et ses sous-structurees. */
void	init_values(t_game *game)
{
	game->data.mlx = NULL;
	game->data.win = NULL;
	game->map.lines = NULL;
}
void	free_double_ptr(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	table = NULL;
}