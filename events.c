/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:47:06 by aboiarin          #+#    #+#             */
/*   Updated: 2023/12/27 19:03:42 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_img *f, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = f->real_min - f->real_max;
	center_i = f->imagine_max - f->imagine_min;
	f->real_max = f->real_max + (center_r - zoom * center_r) / 2;
	f->real_min = f->real_max + zoom * center_r;
	f->imagine_min = f->imagine_min + (center_i - zoom * center_i) / 2;
	f->imagine_max = f->imagine_min + zoom * center_i;
}

static void	move(t_img *f, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = f->real_max - f->real_min;
	center_i = f->imagine_max - f->imagine_min;
	if (direction == 'R')
	{
		f->real_min += center_r * distance;
		f->real_max += center_r * distance;
	}
	else if (direction == 'L')
	{
		f->real_min -= center_r * distance;
		f->real_max -= center_r * distance;
	}
	else if (direction == 'D')
	{
		f->imagine_min -= center_i * distance;
		f->imagine_max -= center_i * distance;
	}
	else if (direction == 'U')
	{
		f->imagine_min += center_i * distance;
		f->imagine_max += center_i * distance;
	}
}

int	key_events(int key, t_img *f)
{
	if (key == KEY_ESC)
	{
		quit(f);
		return (0);
	}
	else if (key == KEY_PLUS)
		zoom(f, 0.5);
	else if (key == KEY_MINUS)
		zoom(f, 2);
	else if (key == KEY_UP || key == KEY_W)
		move(f, 0.2, 'U');
	else if (key == KEY_DOWN || key == KEY_S)
		move(f, 0.2, 'D');
	else if (key == KEY_LEFT || key == KEY_A)
		move(f, 0.2, 'L');
	else if (key == KEY_RIGHT || key == KEY_D)
		move(f, 0.2, 'R');
	else
		return (1);
	win_set(f);
	return (0);
}

int	mouse_events(int key, int x, int y, t_img *f)
{
	if (key == MOUSE_WHEEL_UP)
	{
		zoom(f, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(f, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(f, (double)x / WIDTH, 'R');
		if (y < 0)
			move(f, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (f, (double)y / HEIGHT, 'D');
	}
	else if (key == MOUSE_WHEEL_DOWN)
		zoom(f, 2);
	else
		return (0);
	win_set(f);
	return (0);
}

int	quit(t_img *f)
{
	clean_exit(f);
	return (0);
}