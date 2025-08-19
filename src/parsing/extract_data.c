/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:10:41 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 22:10:42 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Wrong path file\n"), 0);
	close(fd);
	return (1);
}

int	extract_textures(t_game *game, char *line, int type)
{
	int		i;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	path = ft_strtrim(&line[i], " \n");
	if (!path)
		return (0);
	if (!check_path(path))
		return (free(path), 0);
	if (type == 0)
		game->textures.path_no = path;
	else if (type == 1)
		game->textures.path_so = path;
	else if (type == 2)
		game->textures.path_we = path;
	else if (type == 3)
		game->textures.path_ea = path;
	return (1);
}
