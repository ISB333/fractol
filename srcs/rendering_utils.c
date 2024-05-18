/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/18 12:04:11 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*	sin(frequenc * continuous_index + phase) * center + delta)

	sin()) generate smooth oscillations values between -1 and 1.
	then they're scaled and shifted to fit within the range [0, 255]
*/
uint32_t	simple_shaders0(double inst)
{
	unsigned char	rgba[4];
	uint32_t		newcolor;

	rgba[0] = (unsigned char)(sin(0.116 * inst + 4) * 127.5 + 127.25);
	rgba[1] = (unsigned char)(sin(0.0513 * inst + 2) * 127.5 + 127.5);
	rgba[2] = (unsigned char)(sin(0.01 * inst + 1) * 127.5 + 127.5);
	rgba[3] = 255;
	newcolor = RGBA(rgba[0], rgba[1], rgba[2], rgba[3]);
	return (newcolor);
}

uint32_t	simple_shaders1(double inst)
{
	unsigned char	rgba[4];
	uint32_t		newcolor;

	rgba[0] = (unsigned char)(sin(0.277490 * inst + 1) * 127.5 + 127.25);
	rgba[1] = (unsigned char)(sin(0.277490 * inst + 2) * 127.5 + 127.5);
	rgba[2] = (unsigned char)(sin(0.277490 * inst + 4) * 127.5 + 127.5);
	rgba[3] = 255;
	newcolor = RGBA(rgba[0], rgba[1], rgba[2], rgba[3]);
	return (newcolor);
}

uint32_t	simple_shaders2(double instability)
{
	unsigned char	rgba[4];
	uint32_t		newcolor;

	rgba[0] = (unsigned char)(sin(0.116 * instability + 1) * 127.5 + 127.25);
	rgba[1] = (unsigned char)(sin(0.513 * instability + 2) * 127.5 + 127.5);
	rgba[2] = (unsigned char)(sin(0.8 * instability + 4) * 127.5 + 127.5);
	rgba[3] = 255;
	newcolor = RGBA(rgba[0], rgba[1], rgba[2], rgba[3]);
	return (newcolor);
}

//	R,G,B MACROS isolate th r,g,b values from the color given
uint32_t	shaders_smooth(int startcolor, int endcolor, \
							double instability, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / instability);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / instability);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / instability);
	new[0] = (R(startcolor)) + round(pix * increment[0]);
	new[1] = (G(startcolor)) + round(pix * increment[1]);
	new[2] = (B(startcolor)) + round(pix * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	smooth_mode1(double instability)
{
	int	color1;
	int	color2;

	if ((int)instability % 4 == 0)
	{
		color1 = 0x660050FF;
		color2 = 0xFAFF00FF;
	}
	else if ((int)instability % 4 == 1)
	{
		color1 = 0x100050FF;
		color2 = 0xa7e500FF;
	}
	else if ((int)instability % 4 == 2)
	{
		color1 = 0xFA0068FF;
		color2 = 0xFFF700FF;
	}
	else
	{
		color1 = 0x02008AFF;
		color2 = 0x00FFFFFF;
	}
	return (shaders_smooth(color1, color2, instability, 1));
}
