/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/05/06 14:37:30 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
f(z) = (n +/- i)^2 + (n + i)
f(z) = ((n +/- i) * (n +/- i) * -1) + (n +/- i)

*/

// int	losange(double r, t_coord **axis)
// {
// 	int	it;

// 	it = -1;
// 	(*axis)->cr = 0;
// 	(*axis)->ci = 0;
// 	while (++it < 100)
// 	{
// 		r = pow(sqrt(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)), 2) + (*axis)->xr;
// 		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
// 		(*axis)->cr = r;
// 		if ((*axis)->cr > 2 || (*axis)->ci > 2)
// 			return (it);
// 	}
// 	return (0);
// }

double	burning_ship(double r, t_coord **axis)
{
	int	it;

	it = -1;
	(*axis)->cr = 0;
	(*axis)->ci = 0;
	while (++it < 100)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2) + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		if ((*axis)->cr < 0)
			(*axis)->cr *= -1;
		if ((*axis)->ci < 0)
			(*axis)->ci *= -1;
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
			return((float)it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
	}
	return (0);
}

double	nova(double r, t_coord **axis)
{
	int	it;
	double i;
	double denom;
	double zrsquared;
	double zrtemp;
	double zisquared;

	// f(z) = z - ((z^3 - 1) / (3z^2)) + c
	// f() = (1 + 0i) - (1 + 0i)^3 - 1 / 3*(1 + 0i)^2  + (x + yi)
		// cross variation when z = c and mbe z^4
	it = -1;
	(*axis)->cr = 1;
	(*axis)->ci = 0;
	zrsquared = 1;
	zrsquared = 0;
	while (++it < 100)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2);
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2;
		(*axis)->cr = r;
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2);
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2;
		(*axis)->cr = r - 1;
		zrtemp = pow(zrsquared, 2) - pow(zisquared, 2);
		zisquared = zrsquared * zisquared * 3;
		zrsquared = zrtemp * 3;
		r = (*axis)->cr * zrsquared - (*axis)->ci * zisquared;
		i = (*axis)->cr * zisquared + (*axis)->ci * zrsquared;
		denom = pow(zrsquared, 2) + pow(zisquared, 2);
		(*axis)->cr = (r / denom) + (*axis)->xr - (*axis)->cr;
		(*axis)->ci = (i / denom) + (*axis)->yi - (*axis)->ci;

		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
		// if ((*axis)->cr + (*axis)->ci >= 4)
			return((float)it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
	}
	return (0);
}

double	mandelbrot(double r, t_coord **axis)
{
	int	it;

	it = -1;
	(*axis)->cr = 0;
	(*axis)->ci = 0;
	while (++it < 50)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2) + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
		{
			//if shaders == glitch returns it
			
			(*axis)->color = it % 4;
			// return(it);
			// return(((float)it + 1) - log(sqrt((pow((*axis)->cr, 2) + pow((*axis)->ci, 2))) / log(4)));
			return(it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
			// return(it);
			// return((float)it - (log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) - 1) / 2));
			// return((float)it - log2(log(pow((*axis)->cr, 2) + pow((*axis)->ci, 2)) / log(2)));
			// return((float)it - log2(log((*axis)->cr + (*axis)->ci) / log(2)));
		}
	}
	return (0);
}

double	julia(double r, t_coord **axis)
{
	int	it;

	it = -1;
	while (++it < 100)
	{
		r = pow((*axis)->xr, 2) - pow((*axis)->yi, 2) + (*axis)->cr;
		(*axis)->yi = (*axis)->xr * (*axis)->yi * 2 + (*axis)->ci;
		(*axis)->xr = r;
		if (pow((*axis)->xr, 2) + pow((*axis)->yi, 2) >= 4)
			return((float)it - logl(log(pow((*axis)->xr, 2) + pow((*axis)->yi, 2)) / log(2)));
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
