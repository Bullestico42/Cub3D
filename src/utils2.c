/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:22:31 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/19 15:59:26 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

#ifdef __linux__

static void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide(game->data.mlx, game->data.win);
	mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
}

/*Fonction responsable de la fermeture du programme.
Elle prend une string qui sera afficher sur le stderr
et exit avec le code d'erreur donné en paramètre*/
int	destroy_display(t_game *game, char *str, int error_code)
{
	if (game->zbuf)
		free(game->zbuf);
	mlx_mouse_show(game->data.mlx, game->data.win);
	game->mouse_locked = 0;
	if (str != NULL)
		ft_putstr_fd(str, 2);
	enemy_destroy(game, &game->enemy);
	if (game->parsing.brut_file)
		free_double_ptr(game->parsing.brut_file);
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

static void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide();
	mlx_mouse_move(game->data.win, cx, cy);
}

int	destroy_display(t_game *game, char *str, int error)
{
	if (game->zbuf)
		free(game->zbuf);
	mlx_mouse_show();
	game->mouse_locked = 0;
	ft_putstr_fd(str, 2);
	enemy_destroy(game, &game->enemy);
	if (game->parsing.brut_file)
		free_double_ptr(game->parsing.brut_file);
	if (game->data.mlx)
	{
		mlx_destroy_window(game->data.mlx, game->data.win);
		free(game->data.mlx);
	}
	exit(error);
}

#endif

void	lock_mouse(t_game *game)
{
	int	cx;
	int	cy;

	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	hide_and_move_mouse(game, cx, cy);
	game->mouse_locked = 1;
}
