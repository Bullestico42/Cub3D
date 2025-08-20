/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:08:58 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/21 00:28:29 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	set_deltas(t_game *game, t_ray *ray, int x)
{
	ray->camera = 2 * x / (double)game->data.win_width - 1;
	ray->dir_x = game->player.dir_x + game->player.fov_x * ray->camera;
	ray->dir_y = game->player.dir_y + game->player.fov_y * ray->camera;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static t_img	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->textures.img_ea);
		return (&game->textures.img_we);
	}
	if (ray->dir_y > 0)
		return (&game->textures.img_so);
	return (&game->textures.img_no);
}

void	init_tex(t_game *game, t_ray *ray, t_img **tex, t_tex *t)
{
	*tex = select_texture(game, ray);
	if (ray->side == 0)
		t->wall_x = game->player.pos_y + ray->perp_dist * ray->dir_y;
	else
		t->wall_x = game->player.pos_x + ray->perp_dist * ray->dir_x;
	t->wall_x -= floor(t->wall_x);
	t->tex_x = (int)(t->wall_x * (*tex)->width);
	if (ray->side == 0 && ray->dir_x > 0)
		t->tex_x = (*tex)->width - t->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		t->tex_x = (*tex)->width - t->tex_x - 1;
	t->step = 1.0 * (*tex)->height / ray->line_height;
	t->tex_pos = (ray->draw_start - game->data.win_height / 2.0
			+ ray->line_height / 2.0) * t->step;
}

void	raycasting_loop(t_game *game, double *zbuf)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < game->data.win_width)
	{
		set_deltas(game, &ray, x);
		set_directions(&game->player, &ray);
		ft_dda(game, &ray);
		calculate_wall_params(game, &ray);
		draw_wall(game, &ray, x);
		zbuf[x] = ray.perp_dist;
	}
}

void	raycasting(t_game *game)
{
	int		colors[2];
	double	*zbuf;

	zbuf = malloc(sizeof(double) * game->data.win_width);
	if (!zbuf)
		return ;
	colors_and_background(game, colors);
	raycasting_loop(game, zbuf);
	coins_draw(game, zbuf);
	enemy_draw(game, zbuf);
	free(zbuf);
}
