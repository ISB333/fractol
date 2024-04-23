/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/04/23 15:23:21 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ff(t_data *d, t_coord *axis)
{
	if (d)
		free(d);
	if (axis)
		free(axis);
	return (1);
}

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}
