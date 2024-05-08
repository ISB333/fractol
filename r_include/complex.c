/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/05/08 14:54:12 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
			if((*axis)->colormode == 's')
				return ((float)it - log2(log(pow((*axis)->xr, 2) + pow((*axis)->yi, 2)) / log(2)));
			return (it);
		}
	}
	return (0);
}

double	nova(double r, t_coord **axis)
{
	int	it;
	double i;

	double	zrp3;
	double	zip3;
	double	zrp2;
	double	zip2;
	double	zrtemp;
	double	denom;

	// f(z) = z - ((z^3 - 1) / (3z^2)) + c
	// f() = (1 + 0i) - (1 + 0i)^3 - 1 / 3*(1 + 0i)^2  + (x + yi)
		// cross variation when z = c and mbe z^4
	it = -1;
// Initialize z with z_r = 1 and z_i = 0

	while (++it < ESCAPE)
	{
		zrp3 = pow((*axis)->xr, 3);
		zip3 = pow((*axis)->yi, 3) * -1;
		zrtemp = pow((*axis)->xr, 2) - pow((*axis)->yi, 2);
		zip2 = (*axis)->xr * (*axis)->yi * 2;
		zrp2 = zrtemp * 3 - 1;
		zip2 *= 3;
		r = zrp2 * zrp3 - zip2 * zip3;
		i = zrp2 * zip3 + zip2 * zrp3;
		denom = pow(zrp3, 2) + pow(zip3, 2);
		zrp3 = (r / denom);
		zip3 = (i / denom);
		(*axis)->xr = (*axis)->xr - zrp3 + (*axis)->cr;
		(*axis)->yi = (*axis)->yi - zip3 + (*axis)->ci;
		// zrp3 = pow((*axis)->cr, 3);
		// zip3 = pow((*axis)->ci, 3) * -1;
		// zrtemp = pow((*axis)->cr, 2) - pow((*axis)->ci, 2);
		// zip2 = (*axis)->cr * (*axis)->ci * 2;
		// zrp2 = zrtemp * 3 - 1;
		// zip2 *= 3;
		// r = zrp2 * zrp3 - zip2 * zip3;
		// i = zrp2 * zip3 + zip2 * zrp3;
		// denom = pow(zrp3, 2) + pow(zip3, 2);
		// zrp3 = (r / denom);
		// zip3 = (i / denom);
		// (*axis)->cr = (*axis)->cr - zrp3 + (*axis)->xr;
		// (*axis)->ci = (*axis)->ci - zip3 + (*axis)->yi;

		if ((pow((*axis)->xr, 2) + pow((*axis)->yi, 2) >= 4))
		{
			if((*axis)->colormode == 's')
				return ((float)it - log2(log(pow((*axis)->xr, 2) + pow((*axis)->yi, 2)) / log(2)));
			return (it);
		}
		// if ((*axis)->cr + (*axis)->ci >= 4)
			// return((float)it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
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
			if ((*axis)->colormode == 'g')
				return (it);
			else
				// return((float)it - log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) / log(2)));
				return((float)it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / log(128)));
				// return(((float)it + 1) - log(sqrt((pow((*axis)->cr, 2) + pow((*axis)->ci, 2))) / log(4)));
			// return(it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
			// return((float)it - log2(log((*axis)->cr + (*axis)->ci) / log(2)));
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
			if((*axis)->colormode == 's')
				// return ((float)it - log2(log(pow((*axis)->xr, 2) + pow((*axis)->yi, 2)) / log(2)));
			return (it);
		}
	}
	return (0);
}

double	complex_calc(char set, t_coord **axis)
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
