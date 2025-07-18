/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_raw_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 03:16:02 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/18 23:17:01 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//A modifier pour faire une instruction en printf
static void		print_error_map_invalid(void)
{
	printf("Error: Map Invalid\n");
}

//prépare a l'extraction de la carte
static int	extract_raw_map(t_game *game)
{
	int	start;

	game->height = 0;
	start = 8;
	if (game->dmap.brut_file[8][0])
	{
		while (game->dmap.brut_file[start + game->height])
			game->height++;
		if (game->height < 3)
			return (1);
		if (fill_map(game->height, game, &game->dmap.brut_file[8]))
			return (1);
		return (0);
	}
	else
		return (1);
}

//check si les lignes existe et stock les couleurs dans un int *
static int	extract_raw_colors(t_game *game)
{
	int	is_okay;

	is_okay = 0;
	game->state = 0;
	if (game->dmap.brut_file[5][0])
	{
		while (!(ft_isdigit(game->dmap.brut_file[5][game->state])))
			game->state++;
		is_okay += extract_colors(game, 0, 'F');
	}
	else
		return (1);
	game->state = 0;
	if (game->dmap.brut_file[6][0])
	{
		while (!(ft_isdigit(game->dmap.brut_file[6][game->state])))
			game->state++;
		is_okay += extract_colors(game, 0, 'C');
	}
	else
		return (1);
	if (is_okay == 2)
		return (0);
	print_error_map_invalid();
	return (1);
}

//vérifie si les textures sont existante et dans le bonne ordre
static int extract_raw_textures(t_game *game)
{
    int is_okay_daddy;

    is_okay_daddy = 0;
	if (game->dmap.brut_file[0][0])
		is_okay_daddy = extract_textures(game, 0, is_okay_daddy);
	if (game->dmap.brut_file[1][0])
		is_okay_daddy = extract_textures(game, 1, is_okay_daddy);
	if (game->dmap.brut_file[2][0])
		is_okay_daddy = extract_textures(game, 2, is_okay_daddy);
	if (game->dmap.brut_file[3][0])
		is_okay_daddy = extract_textures(game, 3, is_okay_daddy);
	if (is_okay_daddy == 4)
		return (0);
	print_error_map_invalid();
	return (1);
}

//Appelle la logique d'extraction du fichier brut
int	extract_raw(t_game *game)
{
	if (extract_raw_textures(game))
		return (1);
	if (extract_raw_colors(game))
		return (1);
	if (extract_raw_map(game))
	  	return (1);
	free_double_ptr(game->dmap.brut_file);
	return (0);
}
