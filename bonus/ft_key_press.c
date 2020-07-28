/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:15:36 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:11:40 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		ft_red_cross(t_data *d)
{
	ft_exit(d, "You clicked on the red cross ! Ambulance is coming\n", "", 1);
	return (0);
}

static int		ft_key_press(int keycode, t_data *d)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		move_up(d);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move_down(d);
	else if (keycode == KEY_D)
		move_right(d);
	else if (keycode == KEY_A)
		move_left(d);
	else if (keycode == KEY_LEFT)
		look_left(&d->f);
	else if (keycode == KEY_RIGHT)
		look_right(&d->f);
	else if (keycode == KEY_ESC)
		ft_exit(d, "ESC key has been pressed ! byebye\n", "", 1);
	d->f.spr_sorted = 0;
	return (0);
}

void	hook_event(t_data *d)
{
	mlx_hook(d->win_ptr, 2, 1L << 0, ft_key_press, d);
	mlx_hook(d->win_ptr, 17, 1L << 17, ft_red_cross, d);
	return ;
}
