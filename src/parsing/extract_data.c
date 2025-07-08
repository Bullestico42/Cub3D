/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 07:20:22 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/08 03:16:21 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int  get_value(char *str)
{
    int res;
    int i;

    res = -1;
    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) || str[i] == ',' || str[i] == ' ' || str[i] == '\n')
            i++;
        else
            return (-1);
    }
    res = ft_atoi(str);
    if (res < 0 || res > 255)
            return (-1);
    return (res);
}

static int  parse_color(char *str, t_game *game)
{
    int res;

    res = -1;
    res = get_value(&str[game->state]);
    while ((ft_strncmp(&str[game->state], ",", 1)) != 0)
    {
        game->state++;
    }
    game->state += 1;
    return (res);
}

int extract_colors(t_game *game, int i, char name)
{
    i = 0;
    if (game->dmap->brut_file[5][0] == 'F' && name == 'F')
    {
        while (i++ < 3)
        {
            game->textures->color_f[i] = parse_color(&game->dmap->brut_file[5][0], game);
            if (game->textures->color_f[i] < 0)
                return (0);
            printf("F =%d\n", game->textures->color_f[i]);
        }
    }
    else if (game->dmap->brut_file[6][0] == 'C' && name == 'C')
    {
        while (i++ < 3)
        {
            game->textures->color_c[i] = parse_color(&game->dmap->brut_file[6][0], game);
            if (game->textures->color_c[i] < 0)
                return (0);
            printf("C =%d\n", game->textures->color_c[i]);
        }
    }
    else
        return (0);
    return (1);
}

static int  check_name(t_game *game, int name)
{
    int fd;
 
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
    while (game->dmap->brut_file[name][x])
    {
        if (game->dmap->brut_file[name][x] == 't')
        {
            if (name == 0)
                game->textures->path_no = ft_strndup(&game->dmap->brut_file[name][3],
                    ft_strlen(&game->dmap->brut_file[name][3]) - 1);
            else if (name == 1)
                game->textures->path_so = ft_strndup(&game->dmap->brut_file[name][3],
                    ft_strlen(&game->dmap->brut_file[name][3]) - 1);
            else if (name == 2)
                game->textures->path_we = ft_strndup(&game->dmap->brut_file[name][3],
                    ft_strlen(&game->dmap->brut_file[name][3]) - 1);
            else if (name == 3)
                game->textures->path_ea = ft_strndup(&game->dmap->brut_file[name][3],
                    ft_strlen(&game->dmap->brut_file[name][3]) - 1);
        }
        x++;
    }
    is_okay += check_name(game, name);
    return (is_okay);
}
