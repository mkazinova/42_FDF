/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:16:24 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 17:00:24 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int		mouse_press(int button, int x, int y, t_fdf *vis)
{
	if (button == 4 || button == 5)
	{
		if (button == 4 && vis->zoom > 3)
			vis->zoom -= 3;
		else
			vis->zoom += 3;
		mlx_destroy_image(vis->mlx, vis->image);
		mlx_clear_window(vis->mlx, vis->window);
		expose_hook_func(vis);
	}
	if (button == 1 && x < WIN_W && x > 0 && y < WIN_H && y > 0)
	{
		vis->mouse_pressed = 1;
		vis->press_x = x;
		vis->press_y = y;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_fdf *vis)
{
	(void)x;
	(void)y;
	if (button == 1)
		vis->mouse_pressed = 0;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *vis)
{
	if (vis->mouse_pressed)
	{
		if (vis->press_x - x > 25)
			vis->rot_y += 2;
		else if (vis->press_x - x < -25)
			vis->rot_y -= 2;
		if (vis->press_y - y > 25)
			vis->rot_x -= 2;
		else if (vis->press_y - y < -25)
			vis->rot_x += 2;
		mlx_destroy_image(vis->mlx, vis->image);
		mlx_clear_window(vis->mlx, vis->window);
		expose_hook_func(vis);
	}
	return (0);
}
