/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:10:02 by dimatayi          #+#    #+#             */
/*   Updated: 2025/08/19 23:14:22 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COIN_H
# define COIN_H
# define COIN_COLOR_KEY 0x000000

struct					s_game;
typedef struct s_game	t_game;

typedef struct s_img_c
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img_c;

typedef struct s_coin
{
	double	x;
	double	y;
	int		collected;
}	t_coin;

typedef struct s_coins
{
	t_coin	*arr;
	int		count;
	t_img_c	tex;
}	t_coins;

int		coins_init(t_game *g, const char *path);
void	coins_update(t_game *g);
void	coins_draw(t_game *g, double *zbuf);
void	coins_destroy(t_game *g);

#endif
