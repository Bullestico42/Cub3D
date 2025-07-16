/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:58:25 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/15 09:34:40 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//permets de compter le nbr de ligne du fichier .cub
int	count_line(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	if (count <= 2)
		return (0);
	return (count);
}

int	fill_raw(int fd, int n_lines, t_game *game)
{
	char	*line;
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (n_lines + 1));
	if (!tmp)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		tmp[i] = ft_strdup(line);
		if (!tmp[i])
			return (free_double_ptr(tmp), 0);
		free(line);
		i++;
	}
	tmp[i] = NULL;
	game->dmap.brut_file = tmp;
	i = 0;
	while (game->dmap.brut_file[i])
	{
		write(1, game->dmap.brut_file[i], ft_strlen(game->dmap.brut_file[i]));
		i++;
	}
	return (1);
}

int init_file(t_game *game, char *file)
{
	int fd;
	int n_lines;

	fd = 0;
	n_lines = 0;
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		return (printf("Error: Only map with \".cub\" extension"), 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Open File"), 1);
	n_lines = count_line(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	printf("%d\n", n_lines);
	if (!fill_raw(fd, n_lines, game))
		return (1);
	return (0);
}

int	init_data(t_game *game, char *file)
{
	ft_memset(game, 0, (sizeof(t_game)));
	if (init_file(game, file))
		return (1);
	if (extract_raw(game))
		return (1);
	return (0);
}
