/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:02 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:12:15 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_up(t_data *d)
{
	if (d->p.map[(int)(d->f.pos.y)]
	[(int)(d->f.pos.x + d->f.dir.x * MOVES)] != '1')
		d->f.pos.x += d->f.dir.x * MOVES;
	if (d->p.map[(int)(d->f.pos.y + d->f.dir.y * MOVES)]
	[(int)(d->f.pos.x)] != '1')
		d->f.pos.y += d->f.dir.y * MOVES;
	mlx_clear_window(d->mlx_ptr, d->win_ptr);
	ft_process(d);
}

void	move_down(t_data *d)
{
	if (d->p.map[(int)(d->f.pos.y)]
	[(int)(d->f.pos.x - d->f.dir.x * MOVES)] != '1')
		d->f.pos.x -= d->f.dir.x * MOVES;
	if (d->p.map[(int)(d->f.pos.y - d->f.dir.y * MOVES)]
	[(int)(d->f.pos.x)] != '1')
		d->f.pos.y -= d->f.dir.y * MOVES;	
	mlx_clear_window(d->mlx_ptr, d->win_ptr);
	ft_process(d);
}

void	move_right(t_data *d)
{
	if (d->p.map[(int)(d->f.pos.y)]
	[(int)(d->f.pos.x - d->f.dir.x * MOVES)] != '1')
		d->f.pos.x += d->f.plane.x * MOVES;
	if (d->p.map[(int)(d->f.pos.y + d->f.dir.x * MOVES)]
	[(int)(d->f.pos.x)] != '1')
		d->f.pos.y += d->f.plane.y * MOVES;
	mlx_clear_window(d->mlx_ptr, d->win_ptr);
	ft_process(d);
}

void	move_left(t_data *d)
{
	if (d->p.map[(int)(d->f.pos.y)]
	[(int)(d->f.pos.x + d->f.dir.y * MOVES)] != '1')
		d->f.pos.x -= d->f.plane.x * MOVES;
	if (d->p.map[(int)(d->f.pos.y - d->f.dir.x * MOVES)]
	[(int)(d->f.pos.x)] != '1')
		d->f.pos.y -= d->f.plane.y * MOVES;	
	mlx_clear_window(d->mlx_ptr, d->win_ptr);
	ft_process(d);
}
