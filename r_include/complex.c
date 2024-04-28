/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/04/28 10:33:06 by isb3             ###   ########.fr       */
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

/////// WIP ///////
// int	burning_ship(double r, t_coord **axis)
// {
// 	int	it;

//	//f(z) = abs(z)^2 + c

// 	it = -1;
// 	(*axis)->cr = 0;
// 	(*axis)->ci = 0;
// 	while (++it < 100)
// 	{
// 		r = pow((*axis)->cr, 2) + pow((*axis)->ci, 2) * -1 + (*axis)->xr;
// 		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
// 		(*axis)->cr = r;
// 		if ((*axis)->cr > 2 || (*axis)->ci > 2)
// 			return (it);
// 	}
// 	return (0);
// }


// int	nova(double r, t_coord **axis)
// {
// 	int	it;

// 	// f(z) = z - ((z^3 - 1) / (3z^2)) + c
// 	// f() = (1 + 0i) - (1 + 0i)^3 - 1 / 3*(1 + 0i)^2  + (x + yi)
// 		// cross variation when z = c and mbe z^4
// 	it = -1;
// 	(*axis)->cr = 0;
// 	(*axis)->ci = 0;
// 	while (++it < 100)
// 	{
// 		r = pow((*axis)->cr, 2) + pow((*axis)->ci, 2) * -1 + (*axis)->xr;
// 		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
// 		(*axis)->cr = r;
// 		if ((*axis)->cr > 2 || (*axis)->ci > 2)
// 			return (it);
// 	}
// 	return (0);
// }

int	mandelbrot(double r, t_coord **axis)
{
	int	it;

	// f() = (0 + 0i)^2 + (x + yi)

	it = -1;
	(*axis)->cr = 0;
	(*axis)->ci = 0                                              ;
	while (++it < 100)
	{
		r = pow((*axis)->cr, 2) - pow((*axis)->ci, 2) + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		// printf("%f\n", sin((*axis)->ci));
		if ((pow((*axis)->cr, 2) + pow((*axis)->ci, 2) >= 4))
			return (it);
		// if (pow((*axis)->cr, 2) >= 2 || pow((*axis)->ci, 2) >= 2)
		// 	return (it);
	}
	if (it == 100)
		return (0);
	else
		return (it);
}

int	julia(double r, t_coord **axis)
{
	int	it;

	// f() = (x + yi)^2 + (cr * ci)

	it = -1;
	while (++it < 100)
	{
		r = pow((*axis)->xr, 2) - pow((*axis)->yi, 2) + (*axis)->cr;
		(*axis)->yi = (*axis)->xr * (*axis)->yi * 2 + (*axis)->ci;
		(*axis)->xr = r;
		if (pow((*axis)->xr, 2) + pow((*axis)->yi, 2) >= 4)
			return (it);
	}
	return (0);
}

int	complex_calc(char set, t_coord **axis)
{
	if (set == 'j')
		return (julia(0, axis));
	else if (set == 'm')
		return (mandelbrot(0, axis));
	// else if (set == 'n')
	// 	return (nova(0, axis));
	// else if (set == 'b')
	// 	return (burning_ship(0, axis));
	return (0);
}

// int	main(void)
// {
// 	complex_calc(0, 0, 0, 0);
// }
