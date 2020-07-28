/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:28:52 by cmcgahan          #+#    #+#             */
/*   Updated: 2020/03/02 13:30:50 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			ft_strdel(&tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void		ft_free_ntab(char **tab, int len)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (i < len)
		{
			if (tab[i] != NULL)
				ft_strdel(&tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}
