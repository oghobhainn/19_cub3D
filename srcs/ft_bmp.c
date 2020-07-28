/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:37:00 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 13:45:57 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void			shift_bit(char *header, unsigned int value)
{
	header[0] = (unsigned char)(value);
	header[1] = (unsigned char)(value >> 8);
	header[2] = (unsigned char)(value >> 16);
	header[3] = (unsigned char)(value >> 24);
}

static unsigned char		*int_to_rgb(unsigned char *image, int color)
{
	int			blue;
	int			green;
	int			red;

	blue = color % 256;
	green = ((color - blue) / 256) % 256;
	red = ((color - blue) / (256 * 256)) - green / 256;
	image[0] = (unsigned char)blue;
	image[1] = (unsigned char)green;
	image[2] = (unsigned char)red;
	image[3] = (unsigned char)0;
	return (image);
}

static void		create_bmp_header(t_img *img, char *bmp_header)
{
	int			file_size;

	ft_bzero(bmp_header, 54);
	file_size = 14 + 40 + (4 * (img->size.x * img->size.y));
	bmp_header[0] = (unsigned char)('B');
	bmp_header[1] = (unsigned char)('M');
	shift_bit(&bmp_header[2], file_size);
	bmp_header[10] = (unsigned char)(14 + 40);
	bmp_header[14] = (unsigned char)(40);
	shift_bit(&bmp_header[18], img->size.x);
	shift_bit(&bmp_header[22], -img->size.y);
	bmp_header[26] = (unsigned char)(1);
	bmp_header[28] = (unsigned char)(img->bpp);
}

static void			fill_bmp(t_data *d, unsigned char *image, t_img *img, int bmp_fd)
{
	int			i;
	unsigned char		padding[3];
	char			bmp_header[54];
		
	create_bmp_header(img, bmp_header);
	write(bmp_fd, bmp_header, 54);
	i = 0;
	ft_bzero(padding, 3);
	while (i < img->size.y)
	{
		write(bmp_fd, image + (i * 4 * img->size.x), 4 * img->size.x);
		write(bmp_fd, padding, (4 - (img->size.x * img->bpp / 8) % 4) % 4);
		i++;
	}
	if (close(bmp_fd) < 0)
		ft_exit(d, "Error while closing bmp_fd", "", 2);
}

void	create_bmp(t_data *d, t_img *img, char *path)
{
	int			color;
	int			bmp_fd;
	t_coord_int		pos;
	unsigned char		image[img->size.y][img->size.x][img->bpp / 8];

	pos.x = 0;
	while (pos.x < img->size.y)
	{
		pos.y = 0;
		while (pos.y < img->size.x)
		{
			color  = img->colors[(pos.x * img->size.x + pos.y)];
			int_to_rgb(image[pos.x][pos.y], color);
			pos.y++;
		}
		pos.x++;
	}
	if ((bmp_fd = open(path, O_RDWR | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO)) < 0)
		ft_exit(d, "Couldn't create screenshot at ", path, 2);
	fill_bmp(d, (unsigned char *)image, img, bmp_fd);
}
