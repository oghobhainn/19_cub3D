/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:58 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 13:39:13 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strcpy_charfill(char *dst, const char *src, size_t size, char c)
{
	size_t		i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (src[i] && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dst[i] = c;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	my_mlx_pixel_put(t_img *img, t_coord_int pos, int color)
{
	char	*dst;

	dst = (char*)img->colors + (pos.y * img->line_length + pos.x * (img->bpp/8));
	*(unsigned int*)dst = color;
}
