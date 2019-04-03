/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:48:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 17:34:56 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

void	rotate(int keycode, t_fdf *vis)
{
	if (keycode == 0)
		vis->rot_y += 5;
	else if (keycode == 2)
		vis->rot_y -= 5;
	else if (keycode == 13)
		vis->rot_x -= 5;
	else if (keycode == 1)
		vis->rot_x += 5;
	else if (keycode == 12)
		vis->rot_z += 5;
	else if (keycode == 6)
		vis->rot_z -= 5;
}

void	move(int keycode, t_fdf *vis)
{
	if (keycode == 123)
		vis->movement[0] -= 5;
	else if (keycode == 124)
		vis->movement[0] += 5;
	else if (keycode == 125)
		vis->movement[1] -= 5;
	else if (keycode == 126)
		vis->movement[1] += 5;
}

int		key_hook_func(int keycode, t_fdf *vis)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vis->mlx, vis->image);
		mlx_destroy_window(vis->mlx, vis->window);
		exit(0);
	}
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13 ||
		keycode == 12 || keycode == 6 || keycode == 27 || keycode == 24 ||
		(keycode >= 123 && keycode <= 126))
	{
		if ((keycode >= 0 && keycode <= 2) || keycode == 13 ||
			keycode == 12 || keycode == 6)
			rotate(keycode, vis);
		else if (keycode == 27 && vis->zoom > 3)
			vis->zoom -= 3;
		else if (keycode == 24)
			vis->zoom += 3;
		else
			move(keycode, vis);
		mlx_destroy_image(vis->mlx, vis->image);
		mlx_clear_window(vis->mlx, vis->window);
		expose_hook_func(vis);
	}
	return (0);
}

int		close_hook(int button, t_fdf *vis)
{
	(void)button;
	(void)vis;
	exit(0);
	return (0);
}

void	visualize(t_fdf *vis)
{
	vis->mlx = mlx_init();
	vis->window = mlx_new_window(vis->mlx, WIN_W, WIN_H, "Let's FDF");
	mlx_expose_hook(vis->window, expose_hook_func, vis);
	mlx_hook(vis->window, 17, 0, close_hook, vis);
	mlx_hook(vis->window, 2, 0, key_hook_func, vis);
	mlx_hook(vis->window, 4, 0, mouse_press, vis);
	mlx_hook(vis->window, 5, 0, mouse_release, vis);
	mlx_hook(vis->window, 6, 0, mouse_move, vis);
	mlx_do_key_autorepeaton(vis->mlx);
	mlx_loop(vis->mlx);
}
