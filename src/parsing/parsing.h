/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:26:01 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/12 16:15:42 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"
# include "../../headers/cub3d.h"


int     parse_elements(t_game *game);
int		init_data(t_game *game, char *cub_name);
int		extract_raw(t_game *game);
int		extract_textures(t_game *game, char *line, int type);
int		extract_colors(t_game *game, char *line, int type);
int		fill_map(int lines, t_game *game, char **brut_map);
void	find_player_position(t_game *game, int line_index);
void	raycasting(t_game *game);
int		check_walls_1(t_game *game);
int		check_walls_2(t_game *game);
int		check_char(char **map);
char	*skip_spaces(char *line);
int		is_line_empty(char *line);
char	*get_next_line(int fd);

#endif