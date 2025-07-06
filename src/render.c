/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 00:20:27 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/*Initialise la structure de la map en lisant le fichier avec get_next_line.
Chaque ligne lue est stockée dans une liste chaînée.*/
void	create_map(t_game *game, char *map_path)
{
	t_list	*map_row;
	char	*current_line;

	game->map.fd = open(map_path, O_RDONLY);
	if (game->map.fd == -1)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	current_line = get_next_line(game->map.fd);
	if (!current_line)
		destroy_display(game, "Error\nCan't read map\n", 1);
	while (current_line)
	{
		map_row = ft_lstnew(current_line);
		if (!map_row)
			destroy_display(game, "Error\nCan't malloc map line\n", 1);
		ft_lstadd_back(&game->map.lines, map_row);
		current_line = get_next_line(game->map.fd);
	}
}
