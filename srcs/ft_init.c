/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:37:29 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:03:41 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			init_struct_params(t_params *p)
{
	p->win_size.x = 0;
	p->win_size.y = 0;
	p->NO_path = NULL;
	p->SO_path = NULL;
	p->WE_path = NULL;
	p->EA_path = NULL;
	p->S_path = NULL;
	p->floor_color = -1;
	p->ceiling_color = -1;
	p->map = NULL;
	p->map_size.x = 1;
	p->map_size.y = 0;
	p->flag_player = 0;
	p->starting_pos.x = -1;
	p->starting_pos.y = -1;
	p->spr_count = 0;
	p->spr_x = NULL;
	p->spr_y = NULL;
	p->spr_text = NULL;
	p->ok = 0;
}

void			ft_player_direction(t_params *p, t_frame *f, char po)
{
	f->dir.x = 0;
	f->dir.y = 0;
	f->plane.x = 0;
	f->plane.y = 0;
	if (po == 'N')
	{
		f->dir.y = -1;
		f->plane.x = 0.66;
	}
	else if (po == 'E')
	{
		f->dir.x = 1;
		f->plane.y = 0.66;
	}
	else if (po == 'S')
	{
		f->dir.y = 1;
		f->plane.x = -0.66;
	}
	else if (po == 'W')
	{
		f->dir.x = -1;
		f->plane.y = -0.66;
	}
	p->flag_player = 1;
}

void			init_sprites(t_data *d, t_params *p, t_frame *f)
{
	if (!(p->spr_x = malloc(sizeof(double) * (p->spr_count))))
		ft_exit(d, "Malloc error spr_x", "", 2);
	if (!(p->spr_y = malloc(sizeof(double) * (p->spr_count))))
		ft_exit(d, "Malloc error spr_y", "", 2);
	if (!(p->spr_text = malloc(sizeof(char) * (p->spr_count))))
		ft_exit(d, "Malloc error spr_text", "", 2);
	if (!(f->z_buffer = malloc(sizeof(double) * p->win_size.x)))
		ft_exit(d, "Malloc error z_buffer", "", 2);
	if (!(f->spr_order = malloc(sizeof(int) * p->spr_count)))
		ft_exit(d, "Malloc error spr_order", "", 2);
	if (!(f->spr_dist = malloc(sizeof(double) * p->spr_count)))
		ft_exit(d, "malloc error spr_dist", "", 2);
}

static void		init_frame(t_data *d, t_params *p, t_frame *f)
{
	f->hit = 0;
	f->spr_sorted = 0;
	f->pos.x = p->starting_pos.x + 0.5;
	f->pos.y = p->starting_pos.y + 0.5;
	create_texture_img(d, p->NO_path, &f->NO_img);
	create_texture_img(d, p->SO_path, &f->SO_img);
	create_texture_img(d, p->WE_path, &f->WE_img);
	create_texture_img(d, p->EA_path, &f->EA_img);
	create_texture_img(d, p->S_path, &f->S_img);
}

void			init(t_data *d)
{
	t_coord_int	win_size;
	t_img		*img;

	win_size.x = d->p.win_size.x;
	win_size.y = d->p.win_size.y;
	d->mlx_ptr = mlx_init();
	if (d->save == 0)
		d->win_ptr = mlx_new_window(d->mlx_ptr, win_size.x, win_size.y, "Cub3D");
	img = &d->img;
	img->ptr = mlx_new_image(d->mlx_ptr, d->p.win_size.x,
			d->p.win_size.y);
	img->colors = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	img->size.x = d->p.win_size.x;
	img->size.y = d->p.win_size.y;
	init_frame(d, &d->p, &d->f);
}
