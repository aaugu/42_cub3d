/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:08:32 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/12 12:50:03 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "orientation.h"

void	init_sprite(t_data *d, t_sprite *s, t_ray *r, int x)
{
	s->zbuffer = ft_calloc(d->win_width + 1, sizeof * s->zbuffer);
	s->zbuffer[x] = r->wall_dist;
	s->rela_x = s->x - d->player.pos_x;
	s->rela_y = s->y - d->player.pos_y;
	s->inv_det = (1 / (d->player.plane_x * d->player.dir_y
				- d->player.dir_x * d->player.plane_y));
	s->trans_x = s->inv_det * (d->player.dir_y * s->rela_x
			- d->player.dir_x * s->rela_y);
	s->trans_y = s->inv_det * (d->player.plane_x * s->rela_y
			- d->player.plane_y * s->rela_x);
	s->s_screen_x = (int)((d->win_width / 2)
			* (1 + s->trans_x / s->trans_y));
	s->sprite_h = abs((int)(d->win_height / (s->trans_y)));
}

void	start_end(t_data *d, t_sprite *s)
{
	s->draw_start_y = ((-1 * s->sprite_h) / 2) + (d->win_height / 2);
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = (s->sprite_h / 2) + (d->win_height / 2);
	if (s->draw_end_y >= d->win_height)
		s->draw_end_y = d->win_height - 1;
	s->sprite_w = abs((int)(d->win_width / (s->trans_y)));
	s->draw_start_x = ((-1 * s->sprite_w) / 2) + (s->s_screen_x);
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = (s->sprite_w / 2) + (s->s_screen_x);
	if (s->draw_end_x >= d->win_width)
		s->draw_end_x = d->win_width - 1;
}

void	sprite_casting(t_data *d, t_sprite *s, t_ray *r, int x)
{
	int					y;
	int					a;
	unsigned long		c;

	init_sprite(d, s, r, x);
	start_end(d, s);
	y = s->draw_start_y;
	if (x < s->draw_end_x && x >= s->draw_start_x && s->trans_y > 0
		&& x > 0 && x < d->win_width && s->trans_y < s->zbuffer[x])
	{
		s->tex_x = (int)(256 * (x - (-1 * s->sprite_w / 2 + s->s_screen_x))
				* d->texinfo.size / s->sprite_w) / 256;
		while (y < s->draw_end_y)
		{
			a = (y) * 256 - d->win_height * 128 + s->sprite_h * 128;
			s->tex_y = ((a * d->texinfo.size) / s->sprite_h) / 256;
			c = d->textures[SPRITE1][d->texinfo.size * s->tex_y + s->tex_x];
			if (d->trig == 1)
				c = d->textures[SPRITE2][d->texinfo.size * s->tex_y + s->tex_x];
			if ((c & 0x00FFFFFF) != 0)
				d->texture_pixels[y][x] = c;
			y++;
		}
	}
	free(d->sprite.zbuffer);
}
