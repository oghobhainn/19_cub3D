/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:39 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 15:26:12 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		draw_sprite_column(t_data *d, t_frame *f, t_img *img, int stripe)
{
	int		i;
	t_params	*p;
	t_coord_int	spr_img_pos;

	spr_img_pos.x = stripe;
	spr_img_pos.y = f->spr_draw_start.y;
	p = &d->p;
	f->text.x = (int)(256 * fabs(stripe - (-f->spr_size.x / 2 
		+ f->spr_screen_x)) * img->size.x / f->spr_size.x) / 256;
	if (f->spr_inv.y > 0 && stripe >= 0 && stripe < p->win_size.x
		&& f->spr_inv.y < f->z_buffer[stripe])
	{
		while (spr_img_pos.y < f->spr_draw_end.y)
		{
			i = (spr_img_pos.y) 
				* 256 - p->win_size.y * 128 + f->spr_size.y * 128;
			f->text.y = ((i * img->size.y) / f->spr_size.y) / 256;
			if ((img->colors
				[(img->size.y * f->text.y + f->text.x)] & 0x00ffffff) != 0)
				my_mlx_pixel_put(&d->img, spr_img_pos,
					img->colors[(img->size.y * f->text.y + f->text.x)]);
			spr_img_pos.y++;
		}
	}
}

static void		set_sprite_drawing_limits(t_params *p, t_frame *f, int i)
{
	double		inv;
	t_coord_double	spr_diff;

	spr_diff.x = p->spr_x[i] - f->pos.x;
	spr_diff.y = p->spr_y[i] - f->pos.y;
	inv = 1.0 / (f->plane.x * f->dir.y - f->dir.x * f->plane.y);
	f->spr_inv.x = inv * (f->dir.y * spr_diff.x - f->dir.x * spr_diff.y);
	f->spr_inv.y = inv * (f->plane.x * spr_diff.y - f->plane.y * spr_diff.x);
	f->spr_screen_x = ((p->win_size.x / 2) * (1 + f->spr_inv.x / f->spr_inv.y));
	f->spr_size.y = abs((int)(p->win_size.y / (f->spr_inv.y)));
	f->spr_draw_start.y = -f->spr_size.y / 2 + p->win_size.y / 2;
	if(f->spr_draw_start.y < 0) 
		f->spr_draw_start.y = 0;
	f->spr_draw_end.y = f->spr_size.y / 2 + p->win_size.y / 2;
	if(f->spr_draw_end.y >= p->win_size.y)
		f->spr_draw_end.y = p->win_size.y;
	f->spr_size.x = abs((int)(p->win_size.y / (f->spr_inv.y)));
	f->spr_draw_start.x = -f->spr_size.x / 2 + f->spr_screen_x - 1;
	if(f->spr_draw_start.x < 0) 
		f->spr_draw_start.x = 0;
	f->spr_draw_end.x = f->spr_size.x / 2 + f->spr_screen_x + 1;
	if(f->spr_draw_end.x > p->win_size.x)
		f->spr_draw_end.x = p->win_size.x;
}

void			draw_sprites(t_data *d, t_params *p, t_frame *f, t_img *text)
{
	int		i;
	int		j;
	int		stripe;

	i = 0;
	j = 0;
	while (i < p->spr_count || j < p->spr_count)
	{
		if (j == f->spr_order[i] && f->spr_dist[i] > 0.1)
		{
			set_sprite_drawing_limits(p, f, i);
			stripe = f->spr_draw_start.x;
			while (stripe < f->spr_draw_end.x)
			{
				draw_sprite_column(d, f, text, stripe);
				stripe++;
			}
			j++;
			i = -1;
		}
		i++;
	}
}

static void		init_sprite_order(t_params *p, t_frame *f)
{
	int 		i;
	
	i = 0;
	while (i < p->spr_count && !f->spr_sorted)
	{
		f->spr_order[i] = i;
		f->spr_dist[i] =
			((f->pos.x - p->spr_x[i]) * (f->pos.x - p->spr_x[i])
			+ (f->pos.y - p->spr_y[i]) * (f->pos.y - p->spr_y[i]));
		i++;
	}
}

void			sort_sprites(t_params *p, t_frame *f)
{
	t_coord_int	var;
	int		tmp_order;
	
	init_sprite_order(p, f);
	var.x = 0;
	while (var.x < p->spr_count - 1)
	{
		var.z = 0;
		var.y = var.x;
		while (++var.y < p->spr_count)
		{
			if ((f->spr_dist[var.x] < f->spr_dist[var.y]
				&& f->spr_order[var.x] < f->spr_order[var.y])
				|| (f->spr_dist[var.x] > f->spr_dist[var.y]
				&& f->spr_order[var.x] > f->spr_order[var.y]))
			{
				var.z = 1;
				tmp_order = f->spr_order[var.x];
				f->spr_order[var.x] = f->spr_order[var.y];
				f->spr_order[var.y] = tmp_order;
			}
		}
		var.x = (var.z == 0) ? var.x + 1 : var.x;
	}
	f->spr_sorted = 1;
}
