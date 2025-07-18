/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 07:20:22 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/18 23:25:18 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//obtient la valeurs R G B selon l'index
static int  get_value(char *str)
{
    int res;
    int i;
    char *num_start;

    i = 0;
    while (str[i] == ' ')
        i++;
    num_start = &str[i];
    if (!ft_isdigit(str[i]))
        return (-1);
    while (str[i] && ft_isdigit(str[i]))
        i++;
    res = ft_atoi(num_start);
    if (res < 0 || res > 255)
        return (-1);
    return (res);
}

//Avance l'index jusqu'à la prochaine couleur
static int  parse_color(char *str, int *index)
{
    int res;

    while (str[*index] == ' ')
        (*index)++;
    res = get_value(&str[*index]);
    while (str[*index] && ft_isdigit(str[*index]))
        (*index)++;
    while (str[*index] == ' ')
        (*index)++;
    if (str[*index] == ',')
        (*index)++;

    return (res);
}

//Selon son nom la fonction va essayer de parser chacune des couleurs RGB
int extract_colors(t_game *game, int i, char name)
{
    int index;

    i = 0;
    index = 2;
    if (game->dmap.brut_file[5][0] == 'F' && name == 'F')
    {
        while (i++ < 3)
        {
            game->textures.color_f[i] = parse_color(game->dmap.brut_file[5], &index);
            if (game->textures.color_f[i] < 0)
                return (0);
        }
    }
    else if (game->dmap.brut_file[6][0] == 'C' && name == 'C')
    {
        while (i++ < 3)
        {
            game->textures.color_c[i] = parse_color(game->dmap.brut_file[6], &index);
            if (game->textures.color_c[i] < 0)
                return (0);
        }
    }
    else
        return (0);
    return (1);
}

//verifie si le chemin d'accès est valide
static int  check_name(t_game *game, int name)
{
    int fd;

    fd = 0;
    if (name == 0)
        fd = open(game->textures.path_no, O_RDONLY);
    else if (name == 1)
        fd = open(game->textures.path_so, O_RDONLY);
    else if (name == 2)
        fd = open(game->textures.path_we, O_RDONLY);
    else if (name == 3)
        fd = open(game->textures.path_ea, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Wrong path file\n"), 0);
    else
        return (close(fd), 1);
}

//tente d'accéder au chemin d'accès et les stock en data
int extract_textures(t_game *game, int name, int is_okay)
{
    int x;

    x = 0;
    while (game->dmap.brut_file[name][x])
    {
        if (game->dmap.brut_file[name][x] == 't')
        {
            if (name == 0)
                game->textures.path_no = ft_strndup(&game->dmap.brut_file[name][3],
                    ft_strlen(&game->dmap.brut_file[name][3]) - 1);
            else if (name == 1)
                game->textures.path_so = ft_strndup(&game->dmap.brut_file[name][3],
                    ft_strlen(&game->dmap.brut_file[name][3]) - 1);
            else if (name == 2)
                game->textures.path_we = ft_strndup(&game->dmap.brut_file[name][3],
                    ft_strlen(&game->dmap.brut_file[name][3]) - 1);
            else if (name == 3)
                game->textures.path_ea = ft_strndup(&game->dmap.brut_file[name][3],
                    ft_strlen(&game->dmap.brut_file[name][3]) - 1);
        }
        x++;
    }
    is_okay += check_name(game, name);
    return (is_okay);
}
