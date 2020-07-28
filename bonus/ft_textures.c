/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:45 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:08:51 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*get_texture_img(t_frame *f)
{
	t_img	*text_img;

	if (f->side == 0)
	{
		if (f->ray.x >0)
			text_img = &f->EA_img;
		else
			text_img = &f->WE_img;
	}
	else
	{
		if (f->ray.y >0)
			text_img = &f->SO_img;
		else
			text_img = &f->NO_img;
	}
	f->text.x = (int)(f->wall_x * (double)text_img->size.x);
	if(f->side == 0 && f->ray.x > 0)
		f->text.x = text_img->size.x - f->text.x - 1;
	if(f->side == 1 && f->ray.y < 0)
		f->text.x = text_img->size.x - f->text.x - 1;
	return (text_img);
}

void	get_texture(t_data *d, char *line, char *texture)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(&line[2], " ")))
		ft_exit(d, "Failed allocating memory for path ", texture, 2);
	if (ft_memcmp(&tmp[ft_strlen(tmp) - 4], ".xpm", 4))
		ft_exit(d, "Wrong extension for file ", texture, 2);
	if (!ft_strncmp(texture, "NO", 2))
		d->p.NO_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "SO", 2))
		d->p.SO_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "WE", 2))
		d->p.WE_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "EA", 2))
		d->p.EA_path = ft_strdup(tmp);
	if (!ft_strncmp(texture, "S ", 2))
		d->p.S_path = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void	create_texture_img(t_data *d, char *path, t_img *text)
{
	text->ptr =
		mlx_xpm_file_to_image(d->mlx_ptr, path, &text->size.x, &text->size.y);
	if (text->ptr == NULL)
		ft_exit(d, "Probleme de texture :\n	> ", path, 2);
	text->colors = (int*)mlx_get_data_addr(text->ptr, &text->bpp, 
		&text->line_length, &text->endian);
}
