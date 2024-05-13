/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/05/13 12:49:30 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	nova(double r, t_coord **axis)
{
	int	it;

	double	zr;
	double	zi;
	 

	double tmp = 1.0;
	while (++it < ESCAPE)
	{
		zr = (*axis)->xr;
		zi = (*axis)->yi;
		tmp = (pow((*axis)->xr, 2) + pow((*axis)->yi, 2)) * (pow((*axis)->xr, 2) + pow((*axis)->yi, 2));
		(*axis)->xr = (2 * (*axis)->xr * tmp + pow((*axis)->xr, 2) - pow((*axis)->yi, 2)) / (3.0 * tmp);
		(*axis)->yi = (2 * (*axis)->yi * (tmp - zr)) / (3.0 * tmp);
		tmp = pow(((*axis)->xr - zr), 2) + pow(((*axis)->yi - zi), 2);
		if (tmp <= 0.0001)
			return((float)it);
	}
	return (0);
}

double	burning_ship(double r, t_coord **axis)
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
		if ((*axis)->cr < 0)
			(*axis)->cr *= -1;
		if ((*axis)->ci < 0)
			(*axis)->ci *= -1;
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
		{
			if ((*axis)->colormode == 'z')
				return ((float)it - log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) / log(4)));
			if ((*axis)->colormode == 'm')
				return (((float)it - (log(2) / sqrt(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)))) / log(2));
			if ((*axis)->colormode == 's')
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + 
					pow((*axis)->ci, 2)) - 1) / log(333)));
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
			if ((*axis)->colormode == 'z')
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + \
					pow((*axis)->ci, 2)) - 1) / log(4)));
			if ((*axis)->colormode == 'm')
				return (((float)it - (log(2) / sqrt(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)))) / log(2));
			if ((*axis)->colormode == 's')
				return ((float)it - (log2(log(pow((*axis)->cr, 2) + 
					pow((*axis)->ci, 2)) - 1) / log(333)));
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
			if ((*axis)->colormode == 'z')
				return ((float)it - log2(log(pow((*axis)->xr, 2) + \
				pow((*axis)->yi, 2)) / log(4)));
			if ((*axis)->colormode == 'm')
				return (((float)it - (log(2) / sqrt(pow((*axis)->xr, 2) + pow((*axis)->yi, 2)))) / log(2));
			else if ((*axis)->colormode == 's')
				return ((float)it - log2(log(pow((*axis)->xr, 2) + \
				pow((*axis)->yi, 2)) / log(333)));
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
		return (burning_ship(0, axis));
	else if (set == 'n')
		return (nova(0, axis));
	return (0);
}
