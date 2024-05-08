/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/05/08 10:58:32 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	ft_atod(char *nptr)
{
	long double	nbr;
	int		i;
	int		sign;
	int		divider;

	sign = 1;
	i = 0;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i])
	{
		while (nptr[i] >= '0' && nptr[i] <= '9')
			nbr = (nbr * 10) + ((nptr[i++]) - 48);
		if (nptr[i] == '.' || nptr[i] == ',')
			i++;
	}
	nbr *= sign;
	return (divider = pow(10, i - 2), nbr /= divider);
}

int	is_nbr(char *str)
{
	int	i;
	int	k;

	if (!str)
		return (-1);
	i = 0;
	k = -1;
	while (str[i])
		i++;
	while ((str[++k] >= '0' && str[k] <= '9') || str[k] == '.' || str[k] == ',')
		;
	if (k == i)
		return (0);
	return (-1);
}

void	convert_to_axis(double x, double y, t_coord **axis, double zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	// if ((*axis)->x_zoom || (*axis)->y_zoom)
	// {
	// 	(*axis)->xr = ((*axis)->x_zoom - WIDTH / 2) / 300 * zoom + ((x / 300) * zoom) + (*axis)->x_shift;
	// 	(*axis)->yi = ((*axis)->y_zoom - HEIGHT / 2) / 300 * zoom + ((y / 300) * zoom) + (*axis)->y_shift;
	// }
	// else
	// {
		(*axis)->xr = ((x / 300) * zoom) + (*axis)->x_shift;
		(*axis)->yi = ((y / 300) * zoom) + (*axis)->y_shift;
	// }
}

int	ff(t_data *d, t_coord *axis, int status)
{
	if (d)
		free(d);
	if (axis)
		free(axis);
	if (!status)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	return (1);
}

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}

void	command_set(char	*msg)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("Choose one the following possibilities :\n\n", 1);
	ft_putstr_fd(" -1-  Mandelbrot\n", 1);
	ft_putstr_fd("-2.1- Julia Preset 1 (Type Julia 1)\n", 1);
	ft_putstr_fd("-2.2- Julia Preset 2 (Type Julia 2)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset 3 (Type Julia 3)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset of your choices \
(Type Julia *complex number*)\n\n", 1);
}
