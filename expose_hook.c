/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:19:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/03 15:00:13 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	expose_lines(t_fdf *vis)
{
	int		x;
	int		y;

	y = 0;
	while (y < vis->num_lines)
	{
		x = 0;
		while (x < vis->width - 1)
		{
			draw_line(vis, vis->points[y][x], vis->points[y][x + 1], 1);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < vis->width)
	{
		y = 0;
		while (y < vis->num_lines - 1)
		{
			draw_line(vis, vis->points[y][x], vis->points[y + 1][x], 1);
			y++;
		}
		x++;
	}
}

void	init_projection(t_fdf *vis)
{
	int x_off;
	int y_off;
	int x;
	int y;

	x_off = (WIN_W + TAB_SIZE - (vis->zoom * (vis->width - 1))) / 2;
	y_off = (WIN_H - (vis->zoom * (vis->num_lines - 1))) / 2;
	y = 0;
	while (y < vis->num_lines)
	{
		x = 0;
		while (x < vis->width)
		{
			vis->points[y][x].x = x_off + (x * vis->zoom);
			vis->points[y][x].y = y_off + (y * vis->zoom);
			rotate_point(vis, x, y);
			x++;
		}
		y++;
	}
}

void	expose_tab(t_fdf *vis)
{
	t_point		tab_top;
	t_point		tab_bottom;

	tab_top.x = TAB_SIZE;
	tab_top.y = 0;
	tab_top.color = 0xbebebe;
	tab_bottom.x = TAB_SIZE;
	tab_bottom.y = WIN_H - 1;
	tab_bottom.color = 0xbebebe;
	draw_line(vis, tab_top, tab_bottom, 0);
}

void	expose_dot_or_one_line(t_fdf *vis)
{
	if (vis->width == 1 && vis->num_lines == 1)
		draw_line(vis, vis->points[0][0], vis->points[0][0], 1);
	else if (vis->width == 1)
		draw_line(vis, vis->points[0][0], vis->points[1][0], 1);
	else if (vis->num_lines == 1)
		draw_line(vis, vis->points[0][0], vis->points[0][1], 1);
}

int		expose_hook_func(t_fdf *vis)
{
	vis->image = mlx_new_image(vis->mlx, WIN_W, WIN_H);
	vis->data_addr = mlx_get_data_addr(vis->image, &vis->bpp,
		&vis->size_line, &vis->endian);
	init_projection(vis);
	if (vis->width == 1 || vis->num_lines == 1)
		expose_dot_or_one_line(vis);
	else
		expose_lines(vis);
	expose_tab(vis);
	mlx_put_image_to_window(vis->mlx, vis->window, vis->image, 0, 0);
	mlx_string_put(vis->mlx, vis->window, 20, 25, CTRL_COLOR,
		"Controls:");
	mlx_string_put(vis->mlx, vis->window, 20, 55, CTRL_COLOR,
		"ASWDQZ            rotations");
	mlx_string_put(vis->mlx, vis->window, 20, 75, CTRL_COLOR,
		"+ -               zoom");
	mlx_string_put(vis->mlx, vis->window, 20, 95, CTRL_COLOR,
		"arrows            moves");
	mlx_string_put(vis->mlx, vis->window, 20, 135, CTRL_COLOR,
		"Mouse wheel       zoom");
	mlx_string_put(vis->mlx, vis->window, 20, 155, CTRL_COLOR,
		"LeftClick + hold  rotations");
	return (0);
}
