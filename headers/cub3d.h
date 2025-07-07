/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/07 02:25:15 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_map
{
	int		fd;
	char	**lines;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
}				t_data;

typedef struct s_game
{
	t_data	data;
	t_map	map;
}				t_game;

int		destroy_display(t_game *game, char *str, int error);
void	create_map(t_game *game, char *map_path);
void	init_values(t_game *game);
void	free_double_ptr(char **table);

#endif