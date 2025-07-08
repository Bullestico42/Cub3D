/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:58 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/08 03:06:50 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 42
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_dmap
{
	int		height;
	int		width;
	char	**brut_file;
}	t_dmap;

typedef struct s_textures
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	void	*t_no;
	void	*t_so;
	void	*t_we;
	void	*t_ea;
	int		color_c[3];
	int		color_f[3];
}	t_textures;


typedef struct s_data
{
	void		*mlx;
	void		*win;
}				t_data;

typedef struct s_game
{
	t_data		*data;
	t_dmap		*dmap;
	t_textures	*textures;
	char		**map;
	int			player_x;
	int			player_y;
	int			state;
	char		player_or;
}	t_game;

int		destroy_display(t_game *game, char *str, int error);

//PARSING
int init_data(t_game *game, char *cub_name);
int	extract_raw(t_game *game);
int extract_textures(t_game *game, int name, int is_okay);
int extract_colors(t_game *game, int i, char name);
int	fill_map(int lines, t_game *game, char **brut_map);

//GNL
char	*get_next_line(int fd);

//UTILS
void	free_tab(char **tab);

#endif