/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/08/12 15:42:29 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

