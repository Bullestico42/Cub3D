/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:09:38 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 23:17:56 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"
#include "coin.h"

static int	coin_load_texture(t_game *g, t_img_c *t, const char *path)
{
	if (!g || !t || !path)
		return (-1);
	t->img = mlx_xpm_file_to_image(g->data.mlx, (char *)path, &t->w, &t->h);
	if (!t->img)
		return (-1);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	if (!t->addr)
		return (-1);
	return (0);
}

static int	count_char(const char *s, char c)
{
	int	n;

	n = 0;
	while (s && *s)
	{
		if (*s == c)
			n++;
		s++;
	}
	return (n);
}

int	coins_init(t_game *g, const char *path)
{
	int	y;
	int	x;
	int	i;

	g->coins.arr = NULL;
	g->coins.count = 0;
	if (!g || !g->map)
		return (-1);
	y = -1;
	while (g->map[++y])
		g->coins.count += count_char(g->map[y], 'C');
	if (g->coins.count <= 0)
		return (0);
	g->coins.arr = malloc(sizeof(t_coin) * g->coins.count);
	if (!g->coins.arr)
		return (-1);
	y = -1;
	i = 0;
	while (g->map[++y])
	{
		x = -1;
		while (g->map[y][++x])
		{
			if (g->map[y][x] == 'C')
			{
				g->coins.arr[i].x = x + 0.5;
				g->coins.arr[i].y = y + 0.5;
				g->coins.arr[i].collected = 0;
				g->map[y][x] = '0';
				i++;
			}
		}
	}
	if (coin_load_texture(g, &g->coins.tex, path) < 0)
		return (-1);
	return (0);
}

void	coins_destroy(t_game *g)
{
	if (g->coins.tex.img)
	{
		mlx_destroy_image(g->data.mlx, g->coins.tex.img);
		g->coins.tex.img = NULL;
	}
	free(g->coins.arr);
	g->coins.arr = NULL;
	g->coins.count = 0;
}
