/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo <apiscopo@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:08 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/14 16:15:10 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int     enemy_load_texture(t_game *g, t_enemy *e, const char *path)
{
    if (!g || !e || !path)
        return (-1);
    e->tex.img = mlx_xpm_file_to_image(g->data.mlx, (char *)path,
            &e->tex.w, &e->tex.h);
    if (!e->tex.img)
        return (-1);
    e->tex.addr = mlx_get_data_addr(e->tex.img,
            &e->tex.bpp, &e->tex.line_len, &e->tex.endian);
    if (!e->tex.addr)
        return (-1);
    return (0);
}

void    enemy_destroy(t_game *g, t_enemy *e)
{
    if (!g || !e)
        return ;
    if (e->tex.img)
    {
        mlx_destroy_image(g->data.mlx, e->tex.img);
        e->tex.img = NULL;
    }
    e->tex.addr = NULL;
}
