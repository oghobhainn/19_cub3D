/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:36:31 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 15:44:12 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define ROTS		0.25
# define MOVES		0.25
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_DOWN	125
# define KEY_UP		126
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_W		13
# define KEY_M		46
# define KEY_Q		12
# define KEY_ESC	53
# define KEY_P		35
# define KEY_Z		13

# define BLACK		0x00000000
# define WHITE		0x00FFFFFF
# define RED		0x00FF0000
# define LIME		0x0000FF00
# define BLUE		0x000000FF
# define YELLOW		0x00FFFF00
# define CYAN		0x0000FFFF
# define MAGENTA	0x00FF00FF
# define SILVER		0x00C0C0C0
# define GRAY		0x00808080
# define MAROON		0x00800000
# define OLIVE		0x00808000
# define GREEN		0x00008000
# define PURPLE		0x00800080
# define TEAL		0x00008080
# define NAVY		0x00000080
# define INVISIBLE	0xFF000000

typedef struct		s_coord_double
{
	double		x;
	double		y;
	double		z;
}			t_coord_double;

typedef struct		s_coord_int{
	int		x;
	int		y;
	int		z;
}			t_coord_int;

typedef struct  	s_img
{
	void		*ptr;
	int		*colors;
	int		bpp;
	int		line_length;
	int		endian;
	t_coord_int	size;
}               	t_img;

typedef struct 		s_params
{
	int		fd;
	t_coord_int	win_size;
	char		*NO_path;
	char		*SO_path;
	char		*EA_path;
	char		*WE_path;
	char		*S_path;
	int		floor_color;
	int		ceiling_color;
	char		**map;
	t_coord_int	map_size;
	char		player_orientation;
	int		flag_player;
	t_coord_int	starting_pos;
	int		spr_count;
	double		*spr_x;
	double		*spr_y;
	char		*spr_text;
	int		ok;
}               	t_params;

typedef struct 		s_frame
{
	t_coord_double	pos;		//position of the player
	t_coord_double	dir;		//initial direction
	t_coord_double	ray;
	t_coord_double	plane;
	double		camera_x;
	t_coord_double	map;
	t_coord_double	side_dist;
	t_coord_double	delta_dist;
	double		perp_wall_dist;	//perp ray to avoid fish eye effect due to euclidian distance
	t_coord_int	step;		//how much to increase the texture coordinate per screen pixel
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double		wall_x;		//where the wall was hit
	t_img		NO_img;
	t_img		SO_img;
	t_img		EA_img;
	t_img		WE_img;
	t_img		S_img;
	t_coord_int	text;		//coordinate of the texture to draw
	double		*z_buffer;	//contains the distance to the wall of every vertical stripe(instead of every pixel)
	int		*spr_order;
	double		*spr_dist;
	t_coord_double	spr_inv;
	double		spr_screen_x;
	t_coord_int	spr_size;
	t_coord_int	spr_draw_start;
	t_coord_int	spr_draw_end;
	int		spr_sorted;
}			t_frame;

typedef struct 		s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_params	p;
	t_frame		f;
	int		save;
}               	t_data;

void		create_bmp(t_data *data, t_img *img, char *path);

void		get_color(t_data *data, char *line, char c_or_f);

void		ft_exit(t_data *data, char *msg, char *str, int fd);

void		init_struct_params(t_params *params);
void		ft_player_direction(t_params *params, t_frame *frame, char c);
void		init_sprites(t_data *data, t_params *params, t_frame *frame);
void		init(t_data *data);

void		hook_event(t_data *data);
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_right(t_data *data);
void		move_left(t_data *data);
void		look_right(t_frame *f);
void		look_left(t_frame *f);

int		check_map_errors(t_data *d, t_params *p);
void		get_map(t_data *data, char *line, t_params *params);

void		ft_parser(t_data *data, char *file);

int		ft_process(t_data *data);

void		ft_get_resolution(char *line, t_params *params);

void		draw_sprites(t_data *data, t_params *params, t_frame *frame, t_img *textimg);
void		sort_sprites(t_params *params, t_frame *frame);

t_img		*get_texture_img(t_frame *frame);
void		get_texture(t_data *data, char *line, char *texture);
void		create_texture_img(t_data *data, char *path, t_img *text);

int		main(int argc, char **argv);

char		*ft_strcpy_charfill(char *dest, const char *src, size_t size, char c);
void		my_mlx_pixel_put(t_img *img, t_coord_int pos, int color);

#endif
