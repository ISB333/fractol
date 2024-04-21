/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 10:09:54 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
f(z) = (n +/- i)^2 + (n + i)
f(z) = ((n +/- i) * (n +/- i) * -1) + (n +/- i)

*/

int	mandelbrot(double r, double i, double ri[2])
{
	int	it;
	// double ri[2];

	it = -1;

	// ri[0] = 0;
	// ri[1] = 0;
	while (++it < 100)
	{
		r = ri[0] * ri[0] + ri[1] * ri[1] * -1 + 0;
		i = ri[0] * ri[1] + ri[1] * ri[0] + 0;
		ri[0] = r;
		ri[1] = i;
		if (ri[0] > 2 || ri[1] > 2)
			return (it);
	}
	return (0);
}

int	julia(double r, double i, double ri[2])
{
	int	it;
	// double ri[2];

	it = -1;

	// ri[0] = cr;
	// ri[1] = ci;
	// cr = -0.123;
	// ci = 0.736;
	while (++it < 100)
	{
		r = ri[0] * ri[0] + ri[1] * ri[1] * -1 + 0.285;
		i = ri[0] * ri[1] + ri[1] * ri[0] + 0.01;
		ri[0] = r;
		ri[1] = i;
		if (ri[0] > 2 || ri[1] > 2)
			return (it);
	}
	return (0);
}

int	complex_calc(char set, double x, double y)
{
	double	ri[2];
	
	ri[0] = x;
	ri[1] = y;
	if (set == 'j')
		return (julia(0, 0, ri));
	return (mandelbrot(0, 0, ri));
}

// int	main(void)
// {
// 	complex_calc(0, 0, 0, 0);
// }