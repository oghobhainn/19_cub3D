/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:37:19 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:03:09 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_frame(t_data *d, t_frame *f)
{
	mlx_destroy_image(d->mlx_ptr, d->f.NO_img.ptr);
	mlx_destroy_image(d->mlx_ptr, d->f.SO_img.ptr);
	mlx_destroy_image(d->mlx_ptr, d->f.EA_img.ptr);
	mlx_destroy_image(d->mlx_ptr, d->f.WE_img.ptr);
	mlx_destroy_image(d->mlx_ptr, d->f.S_img.ptr);
	free(f->z_buffer);
	f->z_buffer = NULL; 
	free(f->spr_order);
	f->spr_order = NULL;
	free(f->spr_dist);
	f->spr_dist = NULL;
}

static void	free_sprites(t_params *p)
{
	if (p->spr_x != NULL)
		free(p->spr_x);
	if (p->spr_y != NULL)
		free(p->spr_y);
	if (p->spr_text != NULL)
		free(p->spr_text);
	p->spr_x = NULL;
	p->spr_y = NULL;
	p->spr_text = NULL;
}

static void	free_p(t_params *p)
{
	if (p->NO_path != NULL)
		ft_strdel(&p->NO_path);
	if (p->SO_path != NULL)
		ft_strdel(&p->SO_path);
	if (p->WE_path != NULL)
		ft_strdel(&p->WE_path);
	if (p->EA_path != NULL)
		ft_strdel(&p->EA_path);
	if (p->S_path != NULL)
		ft_strdel(&p->S_path);
	free_sprites(p);
	ft_free_ntab(p->map, p->map_size.y);
}

void	ft_exit(t_data *d, char *msg, char *str, int fd)
{
	ft_putstr_fd(msg, fd);
	ft_putstr_fd(str, fd);
	free_p(&d->p);
	if (d->p.ok == 1)
	{
		free_frame(d, &d->f);
		mlx_destroy_image(d->mlx_ptr, d->img.ptr);
		if (d->save == 0)
			mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	}
	exit(0);
}

