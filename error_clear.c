/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:32:38 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/14 17:30:45 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	clear_all(t_fdf *vis)
{
	if (vis)
	{
		if (vis->line)
			ft_strdel(&vis->line);
		if (vis->map)
			ft_strdel(&vis->map);
		free(vis);
		vis = NULL;
	}
}

void	show_error_and_exit(char *error, t_fdf *vis)
{
	ft_putendl(error);
	clear_all(vis);
	exit(0);
}
