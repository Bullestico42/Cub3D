/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/14 20:11:25 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

#if defined(__APPLE__)

static void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide();
	mlx_mouse_move(game->data.win, cx, cy);
}

#else

static void	hide_and_move_mouse(t_game *game, int cx, int cy)
{
	mlx_mouse_hide(game->data.mlx, game->data.win);
	mlx_mouse_move(game->data.mlx, game->data.win, cx, cy);
}

#endif

static void	lock_mouse(t_game *game)
{
	int	cx;
	int	cy;

	cx = game->data.win_width / 2;
	cy = game->data.win_height / 2;
	hide_and_move_mouse(game, cx, cy);
	game->mouse_locked = 1;
	printf("mouselocked\n");
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

int	destroy_display(t_game *game, char *str, int error)
{
	mlx_mouse_show();
	game->mouse_locked = 0;
	ft_putstr_fd(str, 2);
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
// print une instruction a depl vers utils
void	print_instructions(void)
{
	printf("Usage: ./cub3D \"Map name\"\n");
}

/* Responsable d'appeler la foncion qui fermera le programme.
Nécessaire car mlx_hook exige un fonction de ce type :
int (*f)(int keycode, void *param);*/
int	close_game(t_game *game)
{
	return (destroy_display(game, "", 0));
}

void	init_enemy(t_game *game)
{
	if (enemy_init(&game->enemy, 12.5, 6.5, 0.5, 0.25) < 0)
        destroy_display(game, "enemy init fail\n", 1);
	if (enemy_load_texture(game, &game->enemy, "textures/enemy/enemy_1.xpm") < 0)
		destroy_display(game, "enemy texture fail\n", 1);
}

/* Le main vérifie que les pointeur mlx et win sont bien initialisés.
Il permet aussi de fermer la fenêtre avec la croix.*/
int	main(int ac, char **av)
{
	t_game	game;

	if (!(ac >= 2) && !(ac > 3))
		return (print_instructions(), 1);
	if (init_data(&game, av[1]))
		return (1);
	init_values(&game);
	game.data.mlx = mlx_init();
	if (!game.data.mlx)
		destroy_display(&game, "Error\nCan't initialize mlx ptr\n", 1);
	game.data.win = mlx_new_window(game.data.mlx,
			game.data.win_width, game.data.win_height, "Cub3D");
	lock_mouse(&game);
	if (!game.data.win)
		destroy_display(&game, "Error\ncan't generate window\n", 1);
	load_textures(&game);
	if (av[2])
	{
		if ((ft_strncmp(av[2], "bonus", ft_strlen(av[2]))) == 0)
			init_enemy(&game);	
	}
	create_map(&game);
	mlx_loop(game.data.mlx);
	return (0);
}
