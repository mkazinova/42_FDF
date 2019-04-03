/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:29:55 by msnow-be          #+#    #+#             */
/*   Updated: 2019/03/28 12:58:21 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	rotate_point(t_fdf *vis, int x, int y)
{
	int new_x;
	int new_y;
	int new_z;

	new_x = cos(vis->rot_z * RAD_TO_DEG)
	* (vis->points[y][x].x - X_OFF)
	- sin(vis->rot_z * RAD_TO_DEG)
	* (vis->points[y][x].y - Y_OFF) + X_OFF;
	new_y = sin(vis->rot_z * RAD_TO_DEG)
	* (vis->points[y][x].x - X_OFF)
	+ cos(vis->rot_z * RAD_TO_DEG)
	* (vis->points[y][x].y - Y_OFF) + Y_OFF;
	new_z = sin(vis->rot_x * RAD_TO_DEG) * (new_y - Y_OFF) +
	(cos(vis->rot_x * RAD_TO_DEG)
	* (-(vis->points[y][x].z * (vis->zoom / 2))));
	vis->points[y][x].x = sin(vis->rot_y * RAD_TO_DEG) * (new_z)
	+ cos(vis->rot_y * RAD_TO_DEG) * (new_x - X_OFF) + X_OFF;
	vis->points[y][x].y = cos(vis->rot_x * RAD_TO_DEG) * (new_y - Y_OFF)
	+ Y_OFF - sin(vis->rot_x * RAD_TO_DEG)
	* (-(vis->points[y][x].z * vis->zoom / 2));
}
