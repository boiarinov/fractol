/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:41:41 by aboiarin          #+#    #+#             */
/*   Updated: 2023/12/29 19:43:09 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_layout(t_img *f)
{
	if (f->set == JULIA)
	{
		f->x_min = -2.0;
		f->x_max = 2.0;
		f->y_min = -2.0;
		f->y_max = f->y_min
			+ (f->x_max - f->x_min) * HEIGHT / WIDTH;
	}
	else
	{
		f->x_min = -2.0;
		f->x_max = 1.0;
		f->y_max = -1.5;
		f->y_min = f->y_max
			+ (f->x_max - f->x_min) * HEIGHT / WIDTH;
	}
}

void	set_colors(t_img *f, int argc, char **argv)
{
	if (f->set == JULIA && argc == 5)
		f->color = ft_atox(f, argv[4]);
	else if (f->set != JULIA && argc == 3)
		f->color = ft_atox(f, argv[2]);
	if (argc == 2 || (f->set == JULIA && argc == 4))
		f->color = 0xff8c00;
}

void	win_fill(t_img *f)
{
	int		x;
	int		y;
	double	x_pix;
	double	y_pix;
	int		i;

	mlx_clear_window(f->mlx, f->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			x_pix = f->x_min + (double)x * (f->x_max - f->x_min) / WIDTH;
			y_pix = f->y_max + (double)y * (f->y_min - f->y_max) / HEIGHT;
			i = create_fractal(f, x_pix, y_pix);
			color_pixels(f, x, y, f->palette[i]);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

int	create_fractal(t_img *f, double x_pix, double y_pix)
{
	int	i;

	i = 0;
	if (f->set == MANDELBROT)
		i = mandelbrot(x_pix, y_pix);
	else if (f->set == JULIA)
		i = julia(f, x_pix, y_pix);
	return (i);
}
