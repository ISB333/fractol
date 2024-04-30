/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/04/30 12:44:49 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	convert_to_axis(double x, double y, t_coord **axis, float zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);

	// Scale 
	if ((*axis)->x_zoom || (*axis)->y_zoom)
	{
		(*axis)->xr += ((*axis)->x_zoom - WIDTH / 2) / 500;
		(*axis)->yi += ((*axis)->y_zoom - HEIGHT / 2) / 500;
	}
	//if x_zoom > Width / 1 + if y_zoom > Height / 2
	(*axis)->xr = ((x / 500) * zoom) + (*axis)->x_shift;
	(*axis)->yi = ((y / 500) * zoom) + (*axis)->y_shift;
}

int ff(t_data *d, t_coord *axis)
{
	if (d)
		free(d);
	if (axis)
		free(axis);
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
	ft_putstr_fd("-2.3- Julia Preset of your choices (Type Julia *complex number*)\n\n", 1);
}
