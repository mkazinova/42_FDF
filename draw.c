/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:45:45 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 17:35:09 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int		put_pixel(t_fdf *vis, int x, int y, int color)
{
	int		index;
	char	*rgb;

	if (x >= TAB_SIZE && x < WIN_W && y >= 0 && y < WIN_H)
	{
		index = (x * (vis->bpp / 8.0)) + (y * vis->size_line);
		rgb = (char *)&color;
		vis->data_addr[index] = rgb[0];
		index++;
		vis->data_addr[index] = rgb[1];
		index++;
		vis->data_addr[index] = rgb[2];
	}
	return (0);
}

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(double x, double y, t_point start, t_point end)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (end.x - start.x > end.y - start.y)
		percentage = percent(start.x, end.x, x);
	else
		percentage = percent(start.y, end.y, y);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF,
		percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF,
		percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	draw_line(t_fdf *vis, t_point p0, t_point p1, _Bool movable)
{
	double	tx;
	double	dist_x;
	double	dist_y;
	double	x;
	double	y;

	tx = 0.0;
	dist_x = p1.x - p0.x;
	dist_y = p1.y - p0.y;
	while (tx <= 1)
	{
		x = p0.x + dist_x * tx;
		y = p0.y + dist_y * tx;
		if (movable)
		{
			x += vis->movement[0];
			y += vis->movement[1];
		}
		put_pixel(vis, round(x), round(y), get_color(x - vis->movement[0],
			y - vis->movement[1], p0, p1));
		tx += 1. / sqrt((dist_x * dist_x) + (dist_y * dist_y));
	}
}
