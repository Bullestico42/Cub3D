/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:07:00 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 18:55:07 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./close_game.h"

#ifdef __linux__

void	clean_texture(t_game *game)
{
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
}

void	clean_images(t_game *game)
{
	if (game->data.img.image)
		mlx_destroy_image(game->data.mlx, game->data.img.image);
	if (game->data.minimap_img.image)
		mlx_destroy_image(game->data.mlx, game->data.minimap_img.image);
	if (game->textures.img_no.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_no.image);
	if (game->textures.img_so.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_so.image);
	if (game->textures.img_we.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_we.image);
	if (game->textures.img_ea.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_ea.image);
}

#else

void	clean_texture_mac(t_game *game)
{
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_we)
		free(game->textures.path_we);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
}

void	clean_images_mac(t_game *game)
{
	if (game->data.img.image)
		mlx_destroy_image(game->data.mlx, game->data.img.image);
	if (game->data.minimap_img.image)
		mlx_destroy_image(game->data.mlx, game->data.minimap_img.image);
	if (game->textures.img_no.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_no.image);
	if (game->textures.img_so.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_so.image);
	if (game->textures.img_we.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_we.image);
	if (game->textures.img_ea.image)
		mlx_destroy_image(game->data.mlx, game->textures.img_ea.image);
}

#endif