/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@student.42.ai>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2024/07/19 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char    *skip_spaces(char *line)
{
        while (*line == ' ' || *line == '\t')
                line++;
        return (line);
}

int     is_line_empty(char *line)
{
        line = skip_spaces(line);
        if (*line == '\0' || *line == '\n')
                return (1);
        return (0);
}

