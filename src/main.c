/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/08/27 17:20:25 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

// print une instruction a depl vers utils
void	print_instructions(void)
{
	printf("Usage: ./cub3D \"Map name\"\n");
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
		else
			return (destroy_display(&game, "Error, Wrong args\n", 1));
	}
	create_map(&game);
	return (mlx_loop(game.data.mlx), 0);
}
