/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/19 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

typedef struct s_flags
{
        int     tex;
        int     col;
}       t_flags;

static int  handle_tex(t_game *game, char *line, t_flags *f, int idx)
{
        int     mask;

        mask = 1 << idx;
        if ((f->tex & mask) || !extract_textures(game, line, idx))
                return (-1);
        f->tex |= mask;
        return (1);
}

static int  parse_texture_line(t_game *game, char *line, t_flags *f)
{
        if (!ft_strncmp(line, "NO", 2))
                return (handle_tex(game, line, f, 0));
        if (!ft_strncmp(line, "SO", 2))
                return (handle_tex(game, line, f, 1));
        if (!ft_strncmp(line, "WE", 2))
                return (handle_tex(game, line, f, 2));
        if (!ft_strncmp(line, "EA", 2))
                return (handle_tex(game, line, f, 3));
        return (0);
}

static int  parse_color_line(t_game *game, char *line, t_flags *f)
{
        if (line[0] == 'F')
        {
                if (f->col & 1 || !extract_colors(game, line, 0))
                        return (-1);
                f->col |= 1;
        }
        else if (line[0] == 'C')
        {
                if (f->col & 2 || !extract_colors(game, line, 1))
                        return (-1);
                f->col |= 2;
        }
        else
                return (0);
        return (1);
}

static int  parse_element(t_game *game, char *line, t_flags *f)
{
        int     state;

        state = parse_texture_line(game, line, f);
        if (state == -1)
                return (1);
        if (state == 1)
                return (0);
        state = parse_color_line(game, line, f);
        if (state == -1)
                return (1);
        if (state == 1)
                return (0);
        return (1);
}

int     parse_elements(t_game *game, t_flags *flags)
{
        int     i;

        i = 0;
        while (game->dmap.brut_file[i])
        {
                if (is_line_empty(game->dmap.brut_file[i]))
                {
                        i++;
                        continue ;
                }
                if (flags->tex == 15 && flags->col == 3)
                        break ;
                if (parse_element(game,
                                skip_spaces(game->dmap.brut_file[i]),
                                flags))
                        return (-1);
                i++;
        }
        return (i);
}

