/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:45:12 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/12 18:53:33 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	load_texture(t_game *game, t_img *img, char *path)
{
	img->image = mlx_xpm_file_to_image(game->data.mlx, path,
			&img->width, &img->height);
	if (!img->image || img->width <= 0 || img->height <= 0)
		destroy_display(game, "Error\nCan't load texture\n", 1);
	img->addr = mlx_get_data_addr(img->image, &img->bpp,
			&img->line_length, &img->endian);
	if (img->bpp != 32)
		destroy_display(game,
			"Error\nUnsupported texture format\n", 1);
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->textures.img_no, game->textures.path_no);
	load_texture(game, &game->textures.img_so, game->textures.path_so);
	load_texture(game, &game->textures.img_we, game->textures.path_we);
	load_texture(game, &game->textures.img_ea, game->textures.path_ea);
}

unsigned int	get_texture_pixel(t_game *game, t_img *tex, int x, int y)
{
	char	*pixel;

	(void)game;
	pixel = tex->addr + y * tex->line_length + x * (tex->bpp / 8);
	return (*(unsigned int *)pixel);
}
