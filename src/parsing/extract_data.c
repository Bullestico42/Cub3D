/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 07:20:22 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/07 08:45:10 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int  check_name(t_game *game, int name)
{
    int fd;

    printf("%s", game->textures->path_no);
    fd = 0;
    if (name == 0)
        fd = open(game->textures->path_no, O_RDONLY);
    else if (name == 1)
        fd = open(game->textures->path_so, O_RDONLY);
    else if (name == 2)
        fd = open(game->textures->path_we, O_RDONLY);
    else if (name == 3)
        fd = open(game->textures->path_ea, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Wrong path file\n"), 0);
    else
    {
        close(fd);
        return (1);
    }
}

int extract_textures(t_game *game, int name, int is_okay)
{
    int x;

    x = 0;
    while (game->map->brut_file[name][x])
    {
        if (game->map->brut_file[name][x] == 't')
        {
            if (name == 0)
                game->textures->path_no = ft_strndup(&game->map->brut_file[name][3],
                    ft_strlen(&game->map->brut_file[name][3]) - 1);
            else if (name == 1)
                game->textures->path_so = ft_strndup(&game->map->brut_file[name][3],
                    ft_strlen(&game->map->brut_file[name][3]) - 1);
            else if (name == 2)
                game->textures->path_we = ft_strndup(&game->map->brut_file[name][3],
                    ft_strlen(&game->map->brut_file[name][3]) - 1);
            else if (name == 3)
                game->textures->path_ea = ft_strndup(&game->map->brut_file[name][3],
                    ft_strlen(&game->map->brut_file[name][3]) - 1);
        }
        x++;
    }
    is_okay += check_name(game, name);
    return (is_okay);
}
