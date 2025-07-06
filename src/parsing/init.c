/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:58:25 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/07 00:27:23 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

// a depl dans utils
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

//permets de compter le nbr de ligne du fichier .cub
int	count_line(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	if (count <= 2)
		return (0);
	return (count);
}

int	fill_map(int fd, int n_lines, t_game *game)
{
	char	*line;
	int		i;

	game->map->brut_file = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (!game->map->brut_file)
		return (0);
	i = 0;
	while (i < n_lines)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		game->map->brut_file[i] = ft_strdup(line);
		free(line);
		if (!game->map->brut_file[i])
			return (free_tab(game->map->brut_file), 0);
		printf("%s", game->map->brut_file[i]);
		i++;
	}
	game->map->brut_file[i] = NULL;
	return (1);
}

int init_data(t_game *game, char *file)
{
	int fd;
	int n_lines;

	fd = 0;
	n_lines = 0;
	if (!file)
		return (printf("Error: MapFile"), 1);
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		return (printf("Error: Only map with \".cub\" extension"), 1);
	fd = open(file, O_RDONLY);
	if (!fd)
		return (printf("Error: Open File"), 1);
	if (fill_map(fd, n_lines, game))
		return (1);

	return (0);
}
