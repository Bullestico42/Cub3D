/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:52:06 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/21 14:56:45 by apiscopo         ###   ########.fr       */
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