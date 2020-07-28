/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:11 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:15:25 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_map(t_data *d, t_params *p, int x, int y)
{
	char c;

	c = p->map[y][x];
	if (c == ' ')
		return (1);
	if (c == '1')
		return (2);
	if (c == '2' || c == '0')
		return (3);
	if (ft_intheset(c, "NESW") == 1)
	{
		if (p->flag_player == 0)
		{
			ft_player_direction(p, &d->f, c);
			p->starting_pos.x = x;
			p->starting_pos.y = y;
		}
		else
			ft_exit(d, "Deuxieme joueur entre dans l'arene...\
			C'EST L'HEURE DU DUDUDUDUDUDUDUDUEEEEEEEEL jk !", "", 2);
		p->map[y][x] = '0';
		return (4);
	}
	return (0);
}

static void	check_square_neighbors(t_data *d, t_params *p, int x, int y)
{
	int i;
	int j;

	if (p->map[y][x] == '2')
		p->spr_count++;
	i = x - 1;
	while (i <= x + 1)
	{
		j = y - 1;
		while (j <= y + 1)
		{
			if (p->map[j][i] == '\0' || p->map[j][i] == ' ')
				ft_exit(d, "Map not closed", "", 2);
			if (!is_map(d, p, i, j))
				ft_exit(d, "Wrong object in map", "", 2);
			j++;
		}
		i++;
	}
}

int	check_map_errors(t_data *d, t_params *p)
{
	int x;
	int y;

	y = 0;
	while (y < p->map_size.y)
	{
		x = 0;
		while (x < (int)ft_strlen(p->map[y]))
		{
			if ((y == 0 || y == (p->map_size.y - 1))
				&& is_map(d, p, x, y) > 2)
				ft_exit(d, "Map not closed at top or bottom", "", 2);
			if (is_map(d, p, x, y) == 0)
				ft_exit(d, "Wrong object in map", "", 2);
			if (is_map(d, p, x, y) >= 3)
				check_square_neighbors(d, p, x, y);
			x++;
		}
		y++;
	}
	if (p->flag_player == 0)
		ft_exit(d, "Personne pour jouer avec moi :'(", "", 2);
	return(0);
}

static char	**get_tmp_map(t_data *d, t_params *p, char **tmp, char *line)
{
	int i;

	i = 0;
	if (!(tmp = malloc(sizeof(char*) * (p->map_size.y + 1))))
		ft_exit(d, "Malloc error for the tmp map\n", "", 2);
	while (i < p->map_size.y + 1)
	{
		if (!(tmp[i] = malloc(sizeof(char) * (p->map_size.x + 1))))
			ft_exit(d, "Malloc error for the tmp map\n", "", 2);
		if (i != (p->map_size.y))
			tmp[i] = ft_strcpy_charfill
				(tmp[i], p->map[i], p->map_size.x, ' ');
		else
			tmp[i] = ft_strcpy_charfill(tmp[i], line, p->map_size.x, ' ');
		i++;
	}

	return (tmp);
}

void	get_map(t_data *d, char *line, t_params *p)
{
	int	i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (p->map_size.x < (int)ft_strlen(line))
		p->map_size.x = ft_strlen(line);
	tmp = get_tmp_map(d, p, tmp, line);
	ft_free_ntab(p->map, p->map_size.y);
	p->map_size.y = p->map_size.y + 1;
	if (!(p->map = malloc(sizeof(char*) * p->map_size.y)))
		ft_exit(d, "Malloc error for map\n", "", 2);
	while (i < p->map_size.y)
	{
		if (!(p->map[i] = malloc(sizeof(char) * p->map_size.x + 1)))
			ft_exit(d, "malloc error for map\n", "", 2);
		p->map[i] =
			ft_strcpy_charfill(p->map[i], tmp[i], p->map_size.x, ' ');
		ft_strdel(&tmp[i]);
		i++;
	}
	ft_free_tab(tmp);
}
