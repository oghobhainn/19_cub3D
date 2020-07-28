/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:24 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 15:48:50 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		draw_line(t_data *d, t_frame *f, t_img *text_img, int x)
{
	t_coord_int	pos;
	double		step;
	double		texPos;

	pos.x = x;
	pos.y = 0;
	while (pos.y < f->draw_start)
	{
		my_mlx_pixel_put(&d->img, pos, d->p.ceiling_color);
		pos.y++;
	}
	step = 1.0 * text_img->size.y / f->line_height;
	texPos = (f->draw_start - d->p.win_size.y / 2 +
		f->line_height / 2) * step;
	while (pos.y < f->draw_end)
	{
		f->text.y = (int)texPos & (text_img->size.y - 1);
		texPos += step;
		my_mlx_pixel_put(&d->img, pos, text_img->colors
			[(text_img->size.y * f->text.y + f->text.x)]);
		pos.y++;
	}
	pos.y--;
	while (pos.y++ < d->p.win_size.y - 1)
		my_mlx_pixel_put(&d->img, pos, d->p.floor_color);
}

static void		calculations(t_data *d, t_frame *f)
{
	if(f->side == 0)
		f->perp_wall_dist = 
		(f->map.x - f->pos.x + (1 - f->step.x)/2)/ f->ray.x;
	else
		f->perp_wall_dist = 
		(f->map.y - f->pos.y + (1 - f->step.y)/2)/ f->ray.y;
	if (f->side == 0)
		f->wall_x = f->pos.y + f->perp_wall_dist * f->ray.y;
	else
		f->wall_x = f->pos.x + f->perp_wall_dist * f->ray.x;
	
	f->line_height =
		abs((int)(d->p.win_size.y / (f->perp_wall_dist)));
	f->draw_start = -f->line_height / 2 + d->p.win_size.y / 2;
	if(f->draw_start < 0)
		f->draw_start = 0;
	f->draw_end = f->line_height / 2 + d->p.win_size.y / 2;
	if(f->draw_end >= d->p.win_size.y)
		f->draw_end = d->p.win_size.y;
	f->wall_x -= floor((f->wall_x));
}

static void		dda(t_data *d, t_frame *f)
{
	while (f->hit == 0)
	{
		if(f->side_dist.x < f->side_dist.y)
		{
			f->side_dist.x += f->delta_dist.x;
			f->map.x += f->step.x;
			f->side = 0;
		}
		else
		{
			f->side_dist.y += f->delta_dist.y;
			f->map.y += f->step.y;
			f->side = 1;
		}
		if(d->p.map[(int)f->map.y][(int)f->map.x] == '1')
			f->hit = 1;
	}
}

static void		ray(t_data *d, t_frame *f, int x)
{
	f->map.x = (int)f->pos.x;
	f->map.y = (int)f->pos.y;
	f->camera_x = 2 * x /(double)d->p.win_size.x - 1;
	f->ray.x = f->dir.x + f->plane.x * f->camera_x;
	f->ray.y = f->dir.y + f->plane.y * f->camera_x;
	f->hit = 0;
	f->delta_dist.x =
		(f->ray.y == 0) ? 0 : ((f->ray.x == 0) ? 1 : fabs(1 / f->ray.x));
	f->delta_dist.y =
		(f->ray.x == 0) ? 0 : ((f->ray.y == 0) ? 1 : fabs(1 / f->ray.y));
	if (f->ray.x < 0)
		f->step.x = -1;
	else
		f->step.x = 1;
	if (f->ray.y < 0)
		f->step.y = -1;
	else
		f->step.y = 1;
	if (f->ray.x < 0)
		f->side_dist.x = (f->pos.x - f->map.x) * f->delta_dist.x;
	else
		f->side_dist.x = (f->map.x + 1.0 - f->pos.x) * f->delta_dist.x;
	if (f->ray.y < 0)
		f->side_dist.y = (f->pos.y - f->map.y) * f->delta_dist.y;
	else
		f->side_dist.y = (f->map.y + 1.0 - f->pos.y) * f->delta_dist.y;
}

int			ft_process(t_data *d)
{
	int	x;
	t_img	*text_img;

	x = 0;
	while (x < d->p.win_size.x)
	{
		ray(d, &d->f, x);
		dda(d, &d->f);
		d->f.z_buffer[x] = d->f.perp_wall_dist;
		calculations(d, &d->f);
		text_img = get_texture_img(&d->f);
		draw_line(d, &d->f, text_img, x);
		x++;
	}
	sort_sprites(&d->p, &d->f);
	draw_sprites(d, &d->p, &d->f, &d->f.S_img);
	if (d->save == 1)
	{
		create_bmp(d, &d->img, "screenshot.bmp");
		ft_exit(d, "Screenshot cree !\n", "", 1);
	}
	else
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.ptr, 0, 0);
	return (0);
}
