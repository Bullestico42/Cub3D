/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:08:57 by apiscopo          #+#    #+#             */
/*   Updated: 2025/08/20 23:58:07 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H
# define ENEMY_COLOR_KEY 000000

typedef struct s_game	t_game;
typedef struct s_img	t_img;

typedef struct s_img_e
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img_e;

typedef struct s_enemy
{
	double	x;
	double	y;
	double	vx;
	double	vy;
	double	speed;
	double	radius;
	int		alive;
	t_img_e	tex;
}	t_enemy;

int				enemy_init(t_enemy *e, double x, double y);
int				enemy_load_texture(t_game *g, t_enemy *e, const char *path);
void			enemy_destroy(t_game *g, t_enemy *e);
void			enemy_update(t_game *g, double dt);
void			enemy_resolve_collision(t_game *g);
void			enemy_draw(t_game *g, double *zbuf);
void			init_enemy(t_game *game);
int				in_frame_e(t_img *f, int x, int y);
unsigned int	texel_e(t_img_e *t, int x, int y);

#endif
