/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/06 16:57:04 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    dst = game->data.img.addr
        + (y * game->data.img.line_length)
        + (x * (game->data.img.bpp / 8));
    *(unsigned int *)dst = color;
}

void    create_new_image(t_game *game, t_img *img, int width, int height)
{
	img->width = width;
	img->height = height;
	img->image = mlx_new_image(game->data.mlx, width, height);
	if (!img->image)
		destroy_display(game, "Error\nCan't create image\n", 1);
	img->addr = mlx_get_data_addr(img->image,
			&img->bpp, &img->line_length, &img->endian);
}

void    render_images(t_game *game)
{
    mlx_put_image_to_window(game->data.mlx, game->data.win,
            game->data.img.image, 0, 0);
    //create_minimap(game);
    //mlx_put_image_to_window(game->data.mlx, game->data.win,
            //game->data.minimap_img.image, 0, 0);
}

void    create_map(t_game *game)
{
    create_new_image(game, &game->data.img,
            game->data.win_width, game->data.win_height);
    raycasting(game);
    create_new_image(game, &game->data.minimap_img,
            game->data.win_width / 5, game->data.win_width / 5);
    render_images(game);
    mlx_hook(game->data.win, 2, 1L << 0, handle_keypress, game);
    mlx_hook(game->data.win, 6, 1L << 6, handle_mouse_move, game);
    mlx_hook(game->data.win, 17, 0, close_game, game);
}

