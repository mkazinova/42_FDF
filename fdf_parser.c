/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:36:21 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 17:53:13 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>

static char		*add_string(char **current, char **new)
{
	char	*result;
	char	*tmp;

	if (ft_strlen(*current) > 0 && (*current)[ft_strlen(*current) - 1] != ' ')
	{
		tmp = ft_strjoin(*current, " ");
		result = ft_strjoin(tmp, *new);
		free(tmp);
		tmp = NULL;
	}
	else
		result = ft_strjoin(*current, *new);
	free(*current);
	*current = NULL;
	free(*new);
	*new = NULL;
	return (result);
}

int				height_to_color(int height, t_fdf *vis)
{
	int delta;

	delta = (vis->max_height - vis->min_height) / 5;
	if (height >= vis->max_height - delta)
		return (vis->top_color);
	else if (height <= vis->min_height + delta)
		return (vis->bottom_color);
	else
		return (vis->mid_color);
}

int				get_point_color(t_fdf *vis, int pos, int height)
{
	int result;

	while ((vis->map[pos] >= '0' && vis->map[pos] <= '9')
		|| vis->map[pos] == '-')
		pos++;
	if (vis->map[pos] == ' ' || vis->map[pos] == '\0')
		return (height_to_color(height, vis));
	else
	{
		pos += 3;
		result = 0;
		while (vis->map[pos] && vis->map[pos] != ' ')
		{
			result *= 16;
			if ((vis->map[pos] >= '0') && (vis->map[pos] <= '9'))
				result += vis->map[pos] - '0';
			else
				result += 10 + vis->map[pos] - 'a';
			pos++;
		}
		return (result);
	}
}

void			parse_coordinates(t_fdf *vis)
{
	int	x;
	int	y;
	int	pos;

	vis->points = (t_point **)malloc(sizeof(t_point *) * vis->num_lines);
	y = -1;
	pos = 0;
	while (++y < vis->num_lines)
	{
		x = -1;
		vis->points[y] = (t_point *)malloc(sizeof(t_point) * vis->width);
		while (++x < vis->width)
		{
			while (vis->map[pos] == ' ')
				pos++;
			vis->points[y][x].x = x;
			vis->points[y][x].y = y;
			vis->points[y][x].z = ft_atoi(vis->map + pos);
			vis->points[y][x].color = get_point_color(vis, pos,
				vis->points[y][x].z);
			while (vis->map[pos] && vis->map[pos] != ' ')
				pos++;
		}
	}
}

void			fdf_parser(t_fdf *vis, char **argv)
{
	int		fd;

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		show_error_and_exit("Error opening file", vis);
	while (get_next_line_single_fd(fd, &vis->line) > 0)
	{
		if (!check_input(vis))
			show_error_and_exit("Error: Invalid Map", vis);
		vis->map = add_string(&vis->map, &vis->line);
	}
	if (vis->width <= 0)
		show_error_and_exit("Error: Invalid map", vis);
	parse_coordinates(vis);
	close(fd);
}
