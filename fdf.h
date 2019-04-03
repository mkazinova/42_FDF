/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:46:33 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/02 18:07:13 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# define WIN_W			1500
# define WIN_H			1200
# define FIELD_HOR		263
# define FIELD_VER		116
# define TAB_SIZE		300
# define X_OFF			(WIN_W / 2 + TAB_SIZE / 2)
# define Y_OFF			(WIN_H / 2)
# define RAD_TO_DEG		M_PI / 180.0
# define CTRL_COLOR		0xaeaeae

typedef struct			s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}						t_point;

typedef struct			s_fdf
{
	char	*map;
	char	*line;
	int		num_lines;
	int		width;
	int		rot_x;
	int		rot_y;
	int		rot_z;
	int		zoom;
	int		movement[2];
	t_point	**points;
	void	*mlx;
	void	*window;
	void	*image;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		top_color;
	int		mid_color;
	int		bottom_color;
	int		bg_color;
	int		max_height;
	int		min_height;
	_Bool	mouse_pressed;
	int		press_x;
	int		press_y;
}						t_fdf;

_Bool					check_input(t_fdf *vis);
void					clear_all(t_fdf *vis);
void					draw_line(t_fdf *vis, t_point p1, t_point p2,
							_Bool movable);
int						expose_hook_func(t_fdf *vis);
void					fdf_parser(t_fdf *vis, char **argv);
int						get_next_line_single_fd(const int fd, char **line);
int						mouse_move(int x, int y, t_fdf *vis);
int						mouse_press(int button, int x, int y, t_fdf *vis);
int						mouse_release(int button, int x, int y, t_fdf *vis);
void					rotate_point(t_fdf *vis, int x, int y);
void					show_error_and_exit(char *error, t_fdf *vis);
void					visualize(t_fdf *vis);

#endif
