/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:05:59 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/20 18:55:32 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./close_game.h"

/* Responsable d'appeler la foncion qui fermera le programme.
Nécessaire car mlx_hook exige un fonction de ce type :
int (*f)(int keycode, void *param);*/
int	close_game(t_game *game)
{
	return (destroy_display(game, "", 0));
}

#ifdef __linux__

/*Fonction responsable de la fermeture du programme.
Elle prend une string qui sera afficher sur le stderr
et exit avec le code d'erreur donné en paramètre*/
int	destroy_display(t_game *game, char *str, int error_code)
{
	mlx_mouse_show(game->data.mlx, game->data.win);
	game->mouse_locked = 0;
	if (str != NULL)
		ft_putstr_fd(str, 2);
	coins_destroy(game);
	enemy_destroy(game, &game->enemy);
	if (game->parsing.brut_file)
		free_double_ptr(game->parsing.brut_file);
	if (game->map)
		free_double_ptr(game->map);
	clean_texture(game);
	if (game->data.mlx)
		clean_images(game);
	if (game->data.mlx && game->data.win)
		mlx_destroy_window(game->data.mlx, game->data.win);
	if (game->data.mlx)
	{
		mlx_destroy_display(game->data.mlx);
		free(game->data.mlx);
	}
	exit(error_code);
}

#else

int	destroy_display(t_game *game, char *str, int error)
{
	mlx_mouse_show();
	game->mouse_locked = 0;
	ft_putstr_fd(str, 2);
	coins_destroy(game);
	enemy_destroy(game, &game->enemy);
	if (game->parsing.brut_file)
		free_double_ptr(game->parsing.brut_file);
	if (game->map)
		free_double_ptr(game->map);
	clean_texture_mac(game);
	if (game->data.mlx)
	{
		clean_images_mac(game);
		mlx_destroy_window(game->data.mlx, game->data.win);
		free(game->data.mlx);
	}
	exit(error);
}

#endif
