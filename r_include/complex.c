/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:15:22 by adesille          #+#    #+#             */
/*   Updated: 2024/04/19 15:30:34 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
f(z) = (n +/- i)^2 + (n + i)
f(z) = ((n +/- i) * (n +/- i) * -1) + (n +/- i)

*/

int	complex_calc(double r, double i, double cr, double ci)
{
	int	it;
	double ri[2];

	it = -1;

	ri[0] = 0;
	ri[1] = 0;
	// cr = -0.123;
	// ci = 0.736;
	while (++it < 100)
	{
		r = ri[0] * ri[0] + ri[1] * ri[1] * -1 + cr;
		i = ri[0] * ri[1] + ri[1] * ri[0] + ci;
		ri[0] = r;
		ri[1] = i;
		if (ri[0] > 2 || ri[1] > 2)
		{
			// printf("%f, %f Is UnStAbLeEeEe\n", cr, ci);
			return (it);
		}
	}
	// printf("%f, %f IS STABLE\n", cr, ci);
	return (0);
}

// int	main(void)
// {
// 	complex_calc(0, 0, 0, 0);
// }