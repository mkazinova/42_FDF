/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:21:18 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 18:35:46 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static _Bool	check_color(char *line, int *pos)
{
	int color_len;

	*pos += 1;
	if (line[*pos] != '0')
		return (0);
	*pos += 1;
	if (line[*pos] != 'x')
		return (0);
	*pos += 1;
	color_len = 0;
	while (line[*pos] && line[*pos] != ' ' && color_len < 6)
	{
		if (!ft_isdigit(line[*pos]) &&
			!((line[*pos] >= 'A' && line[*pos] <= 'F')
			|| (line[*pos] >= 'a' && line[*pos] <= 'f')))
			return (0);
		if (color_len == 6)
			return (0);
		*pos += 1;
		color_len++;
	}
	if ((line[*pos] && line[*pos] != ' ') || color_len == 0)
		return (0);
	return (1);
}

static _Bool	check_num(t_fdf *vis, int *pos)
{
	if (vis->line[*pos] == '+' || vis->line[*pos] == '-')
		*pos += 1;
	if (!ft_isdigit(vis->line[*pos]))
		return (0);
	while (vis->line[*pos] != ' ' && vis->line[*pos] != '\0')
	{
		if (!ft_isdigit(vis->line[*pos]) && vis->line[*pos] != ',')
			return (0);
		if (vis->line[*pos] == ',')
		{
			if (!check_color(vis->line, pos))
				return (0);
			break ;
		}
		*pos += 1;
	}
	return (1);
}

void			update_max_min_heights_info(t_fdf *vis, int value, int pos)
{
	if (!pos && vis->num_lines == 1)
	{
		vis->max_height = value;
		vis->min_height = value;
	}
	else if (value > vis->max_height)
		vis->max_height = value;
	else if (value < vis->min_height)
		vis->min_height = value;
}

_Bool			check_input(t_fdf *vis)
{
	int pos;
	int	width;

	vis->num_lines++;
	pos = 0;
	width = 0;
	while (vis->line[pos])
	{
		while (vis->line[pos] == ' ')
			pos++;
		if (vis->line[pos])
		{
			update_max_min_heights_info(vis, ft_atoi(vis->line + pos), pos);
			if (!(check_num(vis, &pos)))
				return (0);
			width++;
		}
	}
	if (vis->width == -1)
		vis->width = width;
	else if (vis->width != width)
		return (0);
	return (1);
}
