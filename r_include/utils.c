/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/05/03 13:16:04 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	convert_to_axis(double x, double y, t_coord **axis, float zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	y *= -1;
	if ((*axis)->x_zoom || (*axis)->y_zoom)
	{
		(*axis)->xr += ((*axis)->x_zoom - WIDTH / 2) / 300;
		(*axis)->yi += ((*axis)->y_zoom - HEIGHT / 2) / 300;
		(*axis)->yi *= -1;
	}
	if ((*axis)->x_shift > 0)
	{
		x += (*axis)->x_shift;
		(*axis)->xr = ((x / 300) * zoom);
		(*axis)->yi = ((y / 300) * zoom);
		// printf("%f, %f\n", (*axis)->xr, (*axis)->yi);
	}
	else
	{
		(*axis)->xr = ((x / 300) * zoom);
		(*axis)->yi = ((y / 300) * zoom);
	}
}

int	ff(t_data *d, t_coord *axis, int status)
{
	if (d)
		free(d);
	if (axis)
		free(axis);
	if (!status)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	return (1);
}

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}

void	command_set(char *msg)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("Choose one the following possibilities :\n\n", 1);
	ft_putstr_fd(" -1-  Mandelbrot\n", 1);
	ft_putstr_fd("-2.1- Julia Preset 1 (Type Julia 1)\n", 1);
	ft_putstr_fd("-2.2- Julia Preset 2 (Type Julia 2)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset 3 (Type Julia 3)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset of your choices \
(Type Julia *complex number*)\n\n", 1);
}
