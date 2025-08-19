/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:10:31 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 22:10:32 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	get_value(char *str)
{
	char	*num_start;
	int		res;
	int		i;

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

static t_parsing	parse_color(char *str, int index)
{
	t_parsing	res;

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

static int	set_color(t_game *game, t_parsing res, int i, int type)
{
	if (res.value < 0)
		return (0);
	if (type)
		game->textures.color_c[i] = res.value;
	else
		game->textures.color_f[i] = res.value;
	return (1);
}

static int	check_tail(char *line, int index)
{
	while (line[index] && line[index] != '\n')
	{
		if (line[index] != ' ' && line[index] != '\t')
			return (0);
		index++;
	}
	return (1);
}

int	extract_colors(t_game *game, char *line, int type)
{
	int			i;
	int			index;
	t_parsing	res;

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
