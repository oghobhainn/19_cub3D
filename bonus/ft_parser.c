/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:17 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 15:42:39 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	params_ok(t_data *d, t_params *p, char *line)
{
	if ((!ft_strncmp(line, "R ", 2) && p->win_size.y) ||
		(!ft_strncmp(line, "NO ", 3) && p->NO_path) ||
		(!ft_strncmp(line, "SO ", 3) && p->SO_path) ||
		(!ft_strncmp(line, "EA ", 3) && p->EA_path) ||
		(!ft_strncmp(line, "WE ", 3) && p->WE_path) ||
		(!ft_strncmp(line, "S ", 2) && p->S_path) ||
		(!ft_strncmp(line, "F ", 2) && p->floor_color > -1) ||
		(!ft_strncmp(line, "C ", 2) && p->ceiling_color > -1))
		{	
			printf("floor %d\n", p->floor_color);
			printf("ceil %d\n", p->ceiling_color);
			ft_exit(d, "Une info a ete mise deux fois !\n", "", 2);
		}
	if (p->win_size.x == -1 || p->win_size.y == -1 ||
		p->SO_path == NULL || p->WE_path == NULL ||
		p->EA_path == NULL || p->NO_path == NULL ||
		p->S_path == NULL || p->floor_color == -1 ||
		p->ceiling_color == -1)
		return (0);
	else
		return (1);
}

static int	check_params(t_data *d, t_params *p, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (-1);
	if (line[i] == '1' && params_ok(d, p, &line[i]) == 0)
		ft_exit(d, "Il manque (au moins) une info !\n", "", 2);
	else if (line[i] != '1' && params_ok(d, p, &line[i]))
		ft_exit(d, "Map non-fermee ou symbole invalide\n", "", 2);
	else if (line[i] != '1' && !params_ok(d, p, &line[i])
		&& !(!ft_strncmp(&line[i], "R ", 2) || !ft_strncmp(&line[i], "NO ", 3)
		|| !ft_strncmp(&line[i], "SO ", 3) || !ft_strncmp(&line[i], "WE ", 3)
		|| !ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "S ", 2)
		|| !ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "C ", 2)))
			ft_exit(d, "Il y a une info en trop dans le cubfile\n", "", 2);
	return (i);
}

static void	get_sprites_data(t_data *d, t_params *p, char **map)
{
	t_coord_int	pos;
	int		i;


	pos.y = 1;
	i = 0;
	init_sprites(d, p, &d->f);
	while (pos.y < p->map_size.y - 1 && i < p->spr_count)
	{
		pos.x = 0;
		while (pos.x < p->map_size.x && i < p->spr_count)
		{
			if (map[pos.y][pos.x] >= '2')
				{
					p->spr_x[i] = pos.x + 0.5;
					p->spr_y[i] = pos.y + 0.5;
					p->spr_text[i] = map[pos.y][pos.x];
					i++;
				}
			pos.x++;
		}
		pos.y++;
	}
}

static void	parse_line(t_data *d, char *line)
{
	int	i;

	if ((i = check_params(d, &d->p, line)) == -1)
		return;
	if (ft_strncmp(&line[i], "R ", 2) == 0)
		ft_get_resolution(&line[i], &d->p);
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		get_texture(d, &line[i], "NO");
	if (ft_strncmp(&line[i], "SO", 2) == 0)
		get_texture(d, &line[i], "SO");
	if (ft_strncmp(&line[i], "WE", 2) == 0)
		get_texture(d, &line[i], "WE");
	if (ft_strncmp(&line[i], "EA", 2) == 0)
		get_texture(d, &line[i], "EA");
	if (ft_strncmp(&line[i], "S ", 2) == 0)
		get_texture(d, &line[i], "S ");
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		get_color(d, &line[i], 'F');
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		get_color(d, &line[i], 'C');
	if (line[i] == '1')
		get_map(d, line, &d->p);
}

void	ft_parser(t_data *d, char *cubfile)
{
	int	ret;
	char	*line;

	line = NULL;
	if ((d->p.fd = open(cubfile, O_RDONLY)) < 0)
		ft_exit(d, "Impossible d'ouvrir le fichier .cub\n", "", 2);
	while ((ret = get_next_line(d->p.fd, &line)) > 0)
	{
		parse_line(d, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	check_map_errors(d, &d->p);
	get_sprites_data(d, &d->p, d->p.map);
	if ((close(d->p.fd)) < 0)
		ft_exit(d, "Impossible de fermer le fichier .cub\n", "", 2);
	d->p.ok = 1;
}
