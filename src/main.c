/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/05 21:32:20 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 800, 600, "Cub3D");

	mlx_loop(mlx);
	free(win);

	return (0);
}
