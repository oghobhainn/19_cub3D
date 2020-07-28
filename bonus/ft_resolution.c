/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:33 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 15:42:25 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_get_resolution(char *line, t_params *p)
{
	int	i;
	char	**split_infos;

	i = 0;
	split_infos = ft_split(line, ' ');
	p->win_size.x = ft_atoi(split_infos[1]);
	p->win_size.y = ft_atoi(split_infos[2]);
	ft_free_tab(split_infos);
	if (p->win_size.x < 100)
		p->win_size.x = 100;
	if (p->win_size.y < 100)
		p->win_size.y = 100;
	if (p->win_size.x > 1400)
		p->win_size.x = 1400;
	if (p->win_size.y > 800)
		p->win_size.y = 800;
}
