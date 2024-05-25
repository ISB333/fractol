/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/05/25 08:35:21 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_abs(t_coord **axis)
{
	if ((*axis)->cr < 0)
		(*axis)->cr *= -1;
	if ((*axis)->ci < 0)
		(*axis)->ci *= -1;
}

double	burning_ship(double r, t_coord **axis, int it)
{
	(*axis)->cr = 0;
	(*axis)->ci = 0;
	while (++it < ESCAPE)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2) + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		ft_abs(axis);
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
		{
			if ((*axis)->colormode == 1)
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) - 1) / log(333)));
			if ((*axis)->colormode == 2)
				return ((float)it - log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) / log(4)));
			if ((*axis)->colormode == 4)
				return (((float)it - (log(2) / sqrt(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)))) / log(2));
			return (it);
		}
	}
	return (0);
}

double	mandelbrot(double r, t_coord **axis)
{
	int	it;

	it = -1;
	(*axis)->cr = 0;
	(*axis)->ci = 0;
	while (++it < ESCAPE)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2) + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
		{
			if ((*axis)->colormode == 1)
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) - 1) / log(333)));
			if ((*axis)->colormode == 2)
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) - 1) / log(4)));
			if ((*axis)->colormode == 4)
				return (((float)it - (log(2) / sqrt(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)))) / log(2));
			return (it);
		}
	}
	return (0);
}

double	julia(double r, t_coord **axis)
{
	int	it;

	it = -1;
	while (++it < ESCAPE)
	{
		r = pow((*axis)->xr, 2) - pow((*axis)->yi, 2) + (*axis)->cr;
		(*axis)->yi = (*axis)->xr * (*axis)->yi * 2 + (*axis)->ci;
		(*axis)->xr = r;
		if (pow((*axis)->xr, 2) + pow((*axis)->yi, 2) >= 4)
		{
			if ((*axis)->colormode == 1)
				return ((float)it - log2(log(pow((*axis)->xr, 2) + \
				pow((*axis)->yi, 2)) / log(333)));
			if ((*axis)->colormode == 2)
				return ((float)it - log2(log(pow((*axis)->xr, 2) + \
				pow((*axis)->yi, 2)) / log(4)));
			if ((*axis)->colormode == 4)
				return (((float)it - (log(2) / sqrt(pow((*axis)->xr, 2) + \
					pow((*axis)->yi, 2)))) / log(2));
			return (it);
		}
	}
	return (0);
}

double	complex_calcul(char set, t_coord **axis)
{
	if (set == 'j')
		return (julia(0, axis));
	else if (set == 'm')
		return (mandelbrot(0, axis));
	else if (set == 'b')
		return (burning_ship(0, axis, -1));
	return (0);
}
