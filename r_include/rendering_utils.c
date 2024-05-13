/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/13 12:52:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	mono_shaders(double instability)
{
	uint32_t newcolor;

	union       colour_u
	{
	unsigned int  number;
	unsigned char channels[4];
	};

	union colour_u     c;

	// c.channels[0] = (unsigned char)(sin(0.116 * instability + 4) * 230 + 25);
	// c.channels[1] = (unsigned char)(sin(0.0513 * instability + 2) * 230 + 25);
	// c.channels[2] = (unsigned char)(sin(0.01 * instability + 1) * 230 + 25);
	// c.channels[3] = 255;
	c.channels[0] = (unsigned char)(sin(0.116 * instability + 4) * 127.5 + (127.25));
	c.channels[1] = (unsigned char)(sin(0.0513 * instability + 2) * 127.5 + (127.5));
	c.channels[2] = (unsigned char)(sin(0.01 * instability + 1) * 127.5 + (127.5));
	c.channels[3] = 255;
	newcolor = RGBA(c.channels[0], c.channels[1], c.channels[2], c.channels[3]);
	return (newcolor);
}

uint32_t	simple_shaders(double instability)
{
	int	startcolor;
	int	endcolor;

	if ((int)instability % 4 == 0)
	{
		startcolor = 0xFF001EFF;
		endcolor = 0xFF00A8FF;
	}
	else if ((int)instability % 4 == 1)
	{
		startcolor = 0xFF00A8FF;
		endcolor = 0x1400FFFF;
	}
	else if ((int)instability % 4 == 2)
	{
		startcolor = 0x1400FFFF;
		endcolor = 0x00F0FFFF;
	}
	else
	{
		startcolor = 0x00F0FFFF;
		endcolor = 0x00FF1AFF;
	}
	return (((startcolor / endcolor) ^ (int)instability) * endcolor);
}

uint32_t	shaders_smooth(int startcolor, int endcolor, double instability)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / instability);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / instability);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / instability);
	new[0] = (R(startcolor)) + round(increment[0]);
	new[1] = (G(startcolor)) + round(increment[1]);
	new[2] = (R(startcolor)) + round(increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	glitch_shaders(int startcolor, int endcolor, double len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / len);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / len);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / len);
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
	return (shaders_smooth(color1, color2, instability));
}
