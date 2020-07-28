/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:38:50 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/07/28 14:02:04 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void check_args(t_data *d, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		ft_exit(d, "Le nombre d'arguments n'est pas valide", "", 2);
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		ft_exit(d, "Le deuxieme argument n'est pas --save\n", "", 2);
	else if (argc == 3)
		d->save = 1;
	else
		d->save = 0;
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub"))
		ft_exit(d, "Extension de map invalide\n", "", 2);
	
}

int	main(int argc, char **argv)
{
	t_data d;

	check_args(&d, argc, argv);
	init_struct_params(&d.p);
	ft_parser(&d, argv[1]);
	init(&d);
	if (d.save == 0)
	{
		hook_event(&d);
		mlx_loop_hook(d.mlx_ptr, ft_process, &d);
		mlx_loop(d.mlx_ptr);
	}
	else
		ft_process(&d);
	return (0);
}
