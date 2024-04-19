/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:23:08 by adesille          #+#    #+#             */
/*   Updated: 2024/04/19 15:27:09 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}
