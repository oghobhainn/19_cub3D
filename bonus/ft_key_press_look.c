/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press_look.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:37:51 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 13:49:03 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	look_right(t_frame *f)
{
	double		old_dir_x;
	double		old_plane_x;
	t_coord_double	*plane;

	plane = &f->plane;
	old_dir_x = f->dir.x;
	f->dir.x = old_dir_x * cos(ROTS) - f->dir.y * sin(ROTS);
	f->dir.y = old_dir_x * sin(ROTS) + f->dir.y * cos(ROTS);
	old_plane_x = f->plane.x;
	f->plane.x = old_plane_x * cos(ROTS) - f->plane.y * sin(ROTS);
	f->plane.y = old_plane_x * sin(ROTS) + f->plane.y * cos(ROTS);
}

void	look_left(t_frame *f)
{
	double		old_dir_x;
	double		old_plane_x;
	t_coord_double	*plane;

	plane = &f->plane;
	old_dir_x = f->dir.x;
	f->dir.x = old_dir_x * cos(-ROTS) - f->dir.y * sin(-ROTS);
	f->dir.y = old_dir_x * sin(-ROTS) + f->dir.y * cos(-ROTS);
	old_plane_x = f->plane.x;
	f->plane.x = old_plane_x * cos(-ROTS) - f->plane.y * sin(-ROTS);
	f->plane.y = old_plane_x * sin(-ROTS) + f->plane.y * cos(-ROTS);
}
