/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/05/27 09:17:12 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_in_range(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] >= '0' && str[i] <= '2')
	{
		if (str[i] == '2' && str[i + 1])
			return (1);
		if (str[i + 1] == '.' || str[i + 1] == ',' || !str[i + 1])
			return (0);
	}
	return (1);
}

int	is_burning_ship(char *str1, char *str2)
{
	if (!ft_strcmp("Burning", str1) && !ft_strcmp("Ship", str2))
		return (0);
	if (!ft_strcmp("burning", str1) && !ft_strcmp("Ship", str2))
		return (0);
	if (!ft_strcmp("Burning", str1) && !ft_strcmp("ship", str2))
		return (0);
	if (!ft_strcmp("burning", str1) && !ft_strcmp("ship", str2))
		return (0);
	return (-1);
}

long double	ft_atod(char *nptr, int i, long double nbr, long double decimal)
{
	unsigned long long	div ;
	int					sign;

	div = 1.0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + (nptr[i++] - '0');
	if (nptr[i] == '.' || nptr[i] == ',')
	{
		i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			decimal = (decimal * 10) + (nptr[i++] - '0');
			div *= 10.0;
		}
	}
	return ((nbr + (decimal / div)) * sign);
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
	while ((str[++k] >= '0' && str[k] <= '9') || str[k] == '.' || str[k] == ','\
		|| (str[k] == '-' && (str[k + 1] >= '0' && str[k + 1] <= '9')) || \
			(str[k] == '+' && (str[k + 1] >= '0' && str[k + 1] <= '9')))
		;
	if (k == i)
		return (0);
	return (-1);
}

void	convert_to_axis(double x, double y, t_coord **axis, double zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	if ((*axis)->x_zoom || (*axis)->y_zoom)
	{
		(*axis)->xr = ((x / 300) * zoom) + (((*axis)->x_zoom - (WIDTH / 2)) \
			/ 300) * zoom + (*axis)->x_shift;
		(*axis)->yi = ((y / 300) * zoom) + (((*axis)->y_zoom - (HEIGHT / 2)) \
			/ 300) * zoom + (*axis)->y_shift;
	}
	else
	{
		(*axis)->xr = ((x / 300) * zoom) + (*axis)->x_shift;
		(*axis)->yi = ((y / 300) * zoom) + (*axis)->y_shift;
	}
}
