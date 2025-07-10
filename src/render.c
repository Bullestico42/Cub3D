/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:17:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/07/10 21:02:39 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/* ft_abs retourne la valeur absolue d'un nombre */
double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	return (i);
}

/*
 set_deltas calcule les paramètres principaux du raycasting. Soit la position de la camera, la direction des rayons et les distances delta (différences entre les coordonnées de deux points, en abscisse et en ordonnée)
 */
void	set_deltas(t_game *game, t_ray *ray, int x)
{
	(*ray).camera = 2 * x / (double)game->data.win_width - 1;
	(*ray).dir_x = game->player.dir_x + game->player.fov_x * (*ray).camera;
	(*ray).dir_y = game->player.dir_y + game->player.fov_y * (*ray).camera;
	if ((*ray).dir_x == 0)
		(*ray).delta_dist_x = 1e30;
	else
		(*ray).delta_dist_x = ft_abs(1 / (*ray).dir_x);
	if ((*ray).dir_y == 0)
		(*ray).delta_dist_y = 1e30;
	else
		(*ray).delta_dist_y = ft_abs(1 / (*ray).dir_y);
}

/* set_directions calcule où commence le rayon sur la carte, dans quelle direction il va,
et à quelle distance il touchera les premiers murs sur les axes x et y */
void	set_directions(t_game *game, t_ray *ray)
{
	(*ray).map_x = (int)game->player.pos_x;
	(*ray).map_y = (int)game->player.pos_y;
	if ((*ray).dir_x < 0)
	{
		(*ray).step_x = -1;
		(*ray).side_dist_x = (game->player.pos_x - (*ray).map_x) * (*ray).delta_dist_x;
	}
	else
	{
		(*ray).step_x = 1;
		(*ray).side_dist_x = ((*ray).map_x + 1.0 - game->player.pos_x) * (*ray).delta_dist_x;
	}
	if ((*ray).dir_y < 0)
	{
		(*ray).step_y = -1;
		(*ray).side_dist_y = (game->player.pos_y - (*ray).map_y) * (*ray).delta_dist_y;
	}
	else
	{
		(*ray).step_y = 1;
		(*ray).side_dist_y = ((*ray).map_y + 1.0 - game->player.pos_y) * (*ray).delta_dist_y;
	}
}
/* draw_rays est un fonction inutile utilisé pour le debug. Elle dessine les rayons sur une carte 2D en
partant du joueur et en avançant dans la direction du rayon jusqu’à toucher un mur*/
void	draw_rays(t_game *game, t_ray *ray)
{
	double	ray_pos_x;
	double	ray_pos_y;
	int		px;
	int		py;
	int		offset;

	ray_pos_x = game->player.pos_x;
	ray_pos_y = game->player.pos_y;
	while (game->dmap.brut_file[(int)ray_pos_y][(int)ray_pos_x] != '1')
	{
		px = ray_pos_x * game->data.pixel_size;
		py = ray_pos_y * game->data.pixel_size;
		offset = py * game->data.img.line_length + px * (game->data.img.bpp / 8);
		*(unsigned int *)(game->data.img.addr + offset) = 16711680;
		ray_pos_x += (*ray).dir_x * 0.05;
		ray_pos_y += (*ray).dir_y * 0.05;
	}
}
/* ft_dda utilise l’algorithme DDA pour faire avancer un rayon case par case sur la carte.
À chaque étape, il met à jour sa position et vérifie s’il touche un mur */
void	ft_dda(t_game *game, t_ray *ray)
{
	(*ray).hit = 0;
	while ((*ray).hit == 0)
	{
		if ((*ray).side_dist_x < (*ray).side_dist_y)
		{
			(*ray).side_dist_x += (*ray).delta_dist_x;
			(*ray).map_x += (*ray).step_x;
			//(*ray).side = 0;
		}
		else
		{
			(*ray).side_dist_y += (*ray).delta_dist_y;
			(*ray).map_y += (*ray).step_y;
			//side = 1;
		}
		if (game->dmap.brut_file[(*ray).map_y][(*ray).map_x] == '1')
			(*ray).hit = 1;
	}
}
/* raycasting se charge d'appeller les différentes fonctions constituant le raycasting.
Ces fonctions sont appelé dans une boucle itérant sur la largeur de la fenêtre */
void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < game->data.win_width)
	{
		set_deltas(game, &ray, x);
		set_directions(game, &ray);
		draw_rays(game, &ray);
		ft_dda(game, &ray);
		x++;
	}
}
/* draw_player dessine le joueur à l’écran en coloriant un petit carré autour de sa position,
en fonction de ses coordonnées et de la taille des pixels du jeu. */
void	draw_player(t_game *game)
{
	int		i;
	int		j;
	int		offset;
	int		x;
	int		y;

	i = -2;
	while (i < 2)
	{
		j = -2;
		while (j < 2)
		{
			x = (int)(game->player.pos_x * game->data.pixel_size) + i;
			y = (int)(game->player.pos_y * game->data.pixel_size) + j;
			offset = y * game->data.img.line_length + x * (game->data.img.bpp / 8);
			*(unsigned int *)(game->data.img.addr + offset) = game->player.color;
			j++;
		}
		i++;
	}
}
/* draw_map crée une image avec la mlx, recupère son adresse et appelle les fonction se chargant
du raycasting et de dessiner les player pour ensuite afficher l'image completé à l'écran */
void	create_map(t_game *game)
{
	game->data.img.image = mlx_new_image(game->data.mlx, game->data.win_width, game->data.win_height);
	if (!game->data.img.image)
		destroy_display(game, "Error\nFile can't be open\n", 1);
	game->data.img.addr = mlx_get_data_addr(game->data.img.image, &game->data.img.bpp, &game->data.img.line_length, &game->data.img.endian);
	raycasting(game);
	draw_player(game);
	mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img.image, 0, 0);
}
