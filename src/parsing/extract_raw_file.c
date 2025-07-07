/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_raw_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:16:02 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/07 08:20:15 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void		print_error_map_invalid(void)
{
	printf("Error: Map Invalid\n");
}

/*int	extract_map(t_game *game)
{
	//8
}

static int	extract_raw_colors(t_game *game)
{
	int	is_okay;

	is_okay = 0;
	if (game->map->brut_file[5][0] == 'F')
		is_okay = extract_colors(game, is_okay);
	if (game->map->brut_file[6][0] == 'C')
		is_okay = extract_colors(game, is_okay);
	if (is_okay == 2)
		return (0);
	print_error_map_invalid();
	return (1);
}*/

static int extract_raw_textures(t_game *game)
{
    int is_okay_daddy;

    is_okay_daddy = 0;
	if (game->map->brut_file[0][0] == 'N')
		is_okay_daddy = extract_textures(game, 0, is_okay_daddy);
	if (game->map->brut_file[1][0] == 'S')
		is_okay_daddy = extract_textures(game, 1, is_okay_daddy);
	if (game->map->brut_file[2][0] == 'W')
		is_okay_daddy = extract_textures(game, 2, is_okay_daddy);
	if (game->map->brut_file[3][0] == 'E')
		is_okay_daddy = extract_textures(game, 3, is_okay_daddy);
	if (is_okay_daddy == 4)
		return (0);
	print_error_map_invalid();
	return (1);
}

int	extract_raw(t_game *game)
{
	if (extract_raw_textures(game))
		return (1);
	/*if (extract_raw_colors(game))
		return (1);
	if (extract_raw_map(game))
		return (1);*/
	return (0);
}
