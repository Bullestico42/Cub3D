/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:52:06 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 19:02:14 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_GAME_H
# define CLOSE_GAME_H
# include "../../headers/cub3d.h"

void	clean_texture(t_game *game);
void	clean_images(t_game *game);
void	clean_texture_mac(t_game *game);
void	clean_images_mac(t_game *game);

#endif