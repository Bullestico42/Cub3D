/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:37:11 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/07 00:25:23 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/* Fonction servant initialiser les valeurs dans la structure game et ses sous-structurees. */
void	init_values(t_game *game)
{
	game->data.mlx = NULL;
	game->data.win = NULL;
	game->map.lines = NULL;
}

/* Fonction servant à free les éléments d'une liste chaînée */
void	ft_clearlst(t_list **lst)
{
	t_list	*new_elem;

	while (*lst)
	{
		new_elem = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = new_elem;
	}
	*lst = NULL;
}