/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 02:39:00 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/*Initialise la structure de la map en lisant le fichier avec get_next_line.
Chaque ligne lue est stockée dans un tableau de string.*/
void	create_map(t_game *game, char *map_path)
{
	int	i;

	i = 0;
	game->map.fd = open(map_path, O_RDONLY);
	if (game->map.fd == -1)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	game->map.lines = ft_calloc(15, sizeof(char *));
	if (!game->map.lines)
		destroy_display(game, "Error\nFile can't malloc map\n", 1);
	while (i < 14)
	{
		game->map.lines[i] = ft_calloc(34, sizeof(char));
		if (!game->map.lines[i])
			destroy_display(game, "Error\nFile can't malloc map line\n", 1);
		game->map.lines[i] = get_next_line(game->map.fd);
		if (!game->map.lines[i])
			destroy_display(game, "Error\nCan't read map\n", 1);
		i++;
	}
}