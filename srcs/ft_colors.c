/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:37:11 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:53:06 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_split_colors(char **tab)
{
	int	i;

	i = 0;
	if (tab[0] != '\0' && tab[1] != '\0' && tab[2] != '\0' && tab[3] == '\0')
	{
		if (ft_atoi(tab[0]) > -1
			&& ft_atoi(tab[1]) > -1
			&& ft_atoi(tab[2]) > -1)
			return (0);
	}
	return (-1);
}

static char		**ft_split_colors(t_data *d, char *line)
{
	char	*trim;
	char	**split_colors;

	if (!(trim = ft_strtrim(line, "FC")))	
		ft_exit(d, "Malloc error for FC color", "", 2);
	if (!(split_colors = ft_split(trim, ',')))
	{
		ft_strdel(&trim);
		ft_exit(d, "Malloc error for FC color", "", 2);
	}
	if (check_split_colors(split_colors) != 0)
		ft_exit(d, "Malloc error for ceil or floor", "", 2);
	ft_strdel(&trim);
	return (split_colors);
}

void		get_color(t_data *d, char *line, char c_or_f)
{
	int	color;
	char	**split_colors;
	int	r;
	int	g;
	int	b;

	split_colors = ft_split_colors(d, line);
	r = (ft_atoi(split_colors[0]) <= 255) ? ft_atoi(split_colors[0]) : 255;
	g = (ft_atoi(split_colors[1]) <= 255) ? ft_atoi(split_colors[1]) : 255;
	b = (ft_atoi(split_colors[2]) <= 255) ? ft_atoi(split_colors[2]) : 255;
	color = 65536 * r + 256 * g + b;
	if (c_or_f == 'F')
		d->p.floor_color = color;
	else if (c_or_f == 'C')
		d->p.ceiling_color = color;
	ft_free_tab(split_colors);
}
