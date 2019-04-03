/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:44:26 by msnow-be          #+#    #+#             */
/*   Updated: 2019/04/03 15:01:49 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "stdlib.h"

t_fdf	*initialise_fdf(void)
{
	t_fdf *vis;

	if (!(vis = (t_fdf *)malloc(sizeof(t_fdf))))
		show_error_and_exit("Memory allocation error", NULL);
	vis->num_lines = 0;
	vis->width = -1;
	vis->line = NULL;
	if (!(vis->map = ft_strnew(1)))
		show_error_and_exit("Memory allocation error", vis);
	vis->rot_x = -30;
	vis->rot_y = -30;
	vis->rot_z = 0;
	vis->movement[0] = 0;
	vis->movement[1] = 0;
	vis->max_height = 0;
	vis->min_height = 0;
	vis->top_color = 0x09ff90;
	vis->bottom_color = 0x505099;
	vis->mid_color = 0x90432A;
	vis->bg_color = 0x2f4f4f;
	vis->mouse_pressed = 0;
	return (vis);
}

void	adjust_zoom(t_fdf *vis, int width, int height)
{
	if (width == 1)
		width++;
	if (height == 1)
		height++;
	if (((WIN_W - FIELD_HOR) / (width - 1)) <=
		((WIN_H - FIELD_VER) / (height - 1)))
		vis->zoom = (WIN_W - FIELD_HOR - TAB_SIZE) / (width);
	else
		vis->zoom = (WIN_H - FIELD_VER) / (height);
}

int		parse_color(char *str)
{
	if (!ft_strncmp(str, "cyan\0", 5))
		return (0xffff);
	else if (!ft_strncmp(str, "red\0", 5))
		return (0xff0000);
	else if (!ft_strncmp(str, "green\0", 6))
		return (0xff00);
	else if (!ft_strncmp(str, "yellow\0", 7))
		return (0xffff00);
	else if (!ft_strncmp(str, "orange\0", 7))
		return (0xffa500);
	else if (!ft_strncmp(str, "pink\0", 5))
		return (0xffb5c5);
	else if (!ft_strncmp(str, "purple\0", 7))
		return (0x9b30ff);
	else if (!ft_strncmp(str, "blue\0", 5))
		return (0x505099);
	else
		return (0xbebebe);
}

void	assign_colors(t_fdf *vis, char ***argv)
{
	*argv += 1;
	vis->top_color = parse_color(**argv);
	*argv += 1;
	vis->mid_color = parse_color(**argv);
	*argv += 1;
	vis->bottom_color = parse_color(**argv);
	*argv += 1;
}

int		main(int argc, char **argv)
{
	t_fdf	*vis;
	char	*usage;

	usage = "Usage: ./fdf [-c color1 color1 color3] source_file\n\
		-available colors: red, green, blue, cyan, orange, purple, pink";
	if (argc != 2 && argc != 6)
		show_error_and_exit(usage, NULL);
	vis = initialise_fdf();
	argv++;
	if (argc == 6)
	{
		if (!ft_strncmp(*argv, "-c\0", 3))
			assign_colors(vis, &argv);
		else
			show_error_and_exit(usage, NULL);
	}
	fdf_parser(vis, argv);
	adjust_zoom(vis, vis->width, vis->num_lines);
	visualize(vis);
	clear_all(vis);
	return (0);
}
