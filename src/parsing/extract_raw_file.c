/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_raw_file.c                                 :+:      :+:    :+:   */
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

char    *skip_spaces(char *line);
int     is_line_empty(char *line);
int     parse_elements(t_game *game, t_flags *flags);

static int  extract_map(t_game *game, int start)
{
        int     height;

        height = 0;
        while (game->dmap.brut_file[start + height])
                height++;
        if (height < 3)
                return (printf("Error: Map Invalid\n"), 1);
        if (fill_map(height, game, &game->dmap.brut_file[start]))
                return (1);
        return (0);
}

static int  finalize_map(t_game *game, int i, t_flags *flags)
{
        while (game->dmap.brut_file[i] && is_line_empty(game->dmap.brut_file[i]))
                i++;
        if (flags->tex != 15 || flags->col != 3)
                return (printf("Error: Map Invalid\n"), 1);
        if (!game->dmap.brut_file[i])
                return (printf("Error: Map Invalid\n"), 1);
        if (extract_map(game, i))
                return (1);
        free_double_ptr(game->dmap.brut_file);
        game->dmap.brut_file = NULL;
        return (0);
}

int     extract_raw(t_game *game)
{
        int     index;
        t_flags flags;

        flags.tex = 0;
        flags.col = 0;
        index = parse_elements(game, &flags);
        if (index < 0)
                return (printf("Error: Map Invalid\n"), 1);
        return (finalize_map(game, index, &flags));
}

