/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apiscopo < apiscopo@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/19 15:26:03 by apiscopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// print une instruction a depl vers utils
void	print_instructions(void)
{
	printf("Usage: ./cub3D \"Map name\"\n");
}

void	init_enemy(t_game *game)
{
	if (enemy_init(&game->enemy, 12.5, 6.5, 0.8, 0.7) < 0)
		destroy_display(game, "Error: enemy init fail\n", 1);
	if (enemy_load_texture(game, &game->enemy, "textures/enemy/shrek.xpm") < 0)
		destroy_display(game, "Error: enemy texture fail\n", 1);
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
		destroy_display(&game, "Error: Can't initialize mlx ptr\n", 1);
	game.data.win = mlx_new_window(game.data.mlx,
			game.data.win_width, game.data.win_height, "Cub3D");
	lock_mouse(&game);
	if (!game.data.win)
		destroy_display(&game, "Error: can't generate window\n", 1);
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
