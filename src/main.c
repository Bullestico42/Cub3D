/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bullestico <bullestico@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:36 by bullestico        #+#    #+#             */
/*   Updated: 2025/07/05 22:01:33 by bullestico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"


#ifdef __linux__

void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
}
#else

void	destroy_display(void *mlx)
{
	(void)mlx;
}

#endif

int	main(void)
{
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 800, 600, "Cub3D");

	mlx_loop(mlx);
	destroy_display(mlx);
	free(win);

	return (0);
}
