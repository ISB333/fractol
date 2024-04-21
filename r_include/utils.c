/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 11:13:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ff(t_data *d, t_coord *axis)
{
	if (d)
	{
		// if (d->image)
		// 	free(d->image);
		// if (d->mlx)
		// 	free(d->mlx);
		free(d);
	}
	if (axis)
		free(axis);
	return (1);
}

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}
