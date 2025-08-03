/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/19 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

typedef struct s_parse_color
{
        int     value;
        int     index;
}       t_parse_color;

static int  get_value(char *str)
{
        int     res;
        int     i;
        char    *num_start;

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

static t_parse_color        parse_color(char *str, int index)
{
        t_parse_color   res;

        while (str[index] == ' ')
                index++;
        res.value = get_value(&str[index]);
        while (str[index] && ft_isdigit(str[index]))
                index++;
        while (str[index] == ' ')
                index++;
        if (str[index] == ',')
                index++;
        res.index = index;
        return (res);
}

static int  set_color(t_game *game, t_parse_color res, int i, int type)
{
        if (res.value < 0)
                return (0);
        if (type)
                game->textures.color_c[i] = res.value;
        else
                game->textures.color_f[i] = res.value;
        return (1);
}

static int  check_tail(char *line, int index)
{
        while (line[index] && line[index] != '\n')
        {
                if (line[index] != ' ' && line[index] != '\t')
                        return (0);
                index++;
        }
        return (1);
}

int     extract_colors(t_game *game, char *line, int type)
{
        int             i;
        int             index;
        t_parse_color   res;

        i = 0;
        index = 1;
        while (i < 3)
        {
                res = parse_color(line, index);
                if (!set_color(game, res, i, type))
                        return (0);
                index = res.index;
                i++;
        }
        return (check_tail(line, index));
}

