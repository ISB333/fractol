/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:55:30 by adesille          #+#    #+#             */
/*   Updated: 2024/05/21 10:29:54 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	convert_rgba(uint8_t values[4])
{
	return (((values[0]) << 24) + ((values[1]) << 16) + ((values[2]) << 8) \
		+ (values[3]));
}

int	convert_rgb(int values[3])
{
	return (((values[0]) << 16) + ((values[1]) << 8) + (values[2]));
}

int	ff(t_data *d, t_coord *axis, int status)
{
	if (d)
		free(d);
	if (axis)
		free(axis);
	if (!status)
		return (exit(EXIT_SUCCESS), 0);
	else
		return (exit(EXIT_FAILURE), 1);
	return (1);
}

int	error(void)
{
	perror(mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}

void	command_set(char *msg)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("Choose one the following possibilities :\n\n", 1);
	ft_putstr_fd(" -1-  Mandelbrot\n", 1);
	ft_putstr_fd("-2.1- Julia Preset 1 (Type Julia 1)\n", 1);
	ft_putstr_fd("-2.2- Julia Preset 2 (Type Julia 2)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset 3 (Type Julia 3)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset of your choices \
(Type Julia *complex number*)\n", 1);
	ft_putstr_fd(" -3-  Burning Ship\n", 1);
}
