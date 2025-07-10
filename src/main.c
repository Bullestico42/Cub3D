/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/10 08:06:27 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

#ifdef __linux__

/*Fonction responsable de la fermeture du programme.
Elle prend une string qui sera afficher sur le stderr
et exit avec le code d'erreur donné en paramètre*/
int	destroy_display(t_game *game, char *str, int error_code)
{
	ft_putstr_fd(str, 2);
	if (game->map.fd >= 0)
		close(game->map.fd);
	if (game->map.lines)
		free_double_ptr(game->map.lines);
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
	ft_putstr_fd(str, 2);
	if (game->data->mlx)
	{
		mlx_destroy_window(game->data->mlx, game->data->win);
		free(game->data->mlx);
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

/* Le main vérifie que les pointeur mlx et win sont bien initialisés.
Il permet aussi de fermer la fenêtre avec la croix.*/
int	main(int ac, char **av)
{
	t_game *game;

	game = malloc(sizeof *game);
	if (!game)
    	return (perror("malloc game"), 1);
	if (ac != 2)
		return (print_instructions(), 1);
	if (init_data(game, av[1]))
		return (1);
	printf("PARSING OKAY\n");
	init_values(&game);
	game->data->mlx = mlx_init();
	if (!game->data->mlx)
		destroy_display(game, "Error\nCan't initialize mlx ptr\n", 1);
	game->data->win = mlx_new_window(game->data->mlx, game->data.win_width, game->data.win_heigth, "Cub3D");
	if (!game->data->win)
		destroy_display(game, "Error\ncan't generate window\n", 1);
	create_map(&game, av[1]);
	mlx_hook(game->data->win, 17, 0, close_game, &game);
	mlx_loop(game->data->mlx);
	return (0);
}
