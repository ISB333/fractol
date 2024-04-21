/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 12:15:26 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
f(z) = (n +/- i)^2 + (n + i)
f(z) = ((n +/- i) * (n +/- i) * -1) + (n +/- i)

*/

int	mandelbrot(double r, t_coord **axis)
{
	int	it;

	it = -1;
	(*axis)->cr = 0;
	(*axis)->ci = 0;
	while (++it < 100)
	{
		r = pow((*axis)->cr, 2) + pow((*axis)->ci, 2) * -1 + (*axis)->xr;
		(*axis)->ci = (*axis)->cr * (*axis)->ci * 2 + (*axis)->yi;
		(*axis)->cr = r;
		if ((*axis)->cr > 2 || (*axis)->ci > 2)
			return (it);
	}
	return (0);
}

int	julia(double r, t_coord **axis)
{
	int	it;

	it = -1;
	while (++it < 100)
	{
		r = pow((*axis)->xr, 2) + pow((*axis)->yi, 2) * -1 + (*axis)->cr;
		(*axis)->yi = (*axis)->xr * (*axis)->yi * 2 + (*axis)->ci;
		(*axis)->xr = r;
		if ((*axis)->xr > 2 || (*axis)->yi > 2)
			return (it);
	}
	return (0);
}

int	complex_calc(char set, t_coord **axis)
{
	if (set == 'j')
		return (julia(0, axis));
	return (mandelbrot(0, axis));
}

// int	main(void)
// {
// 	complex_calc(0, 0, 0, 0);
// }
