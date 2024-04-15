/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:09:55 by adesille          #+#    #+#             */
/*   Updated: 2024/04/15 09:11:34 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

int	fractol()
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();	
	if(!mlx_ptr)
		return (-1);
	mlx_terminate(mlx);
	return (0);
}

int main()
{
	fractol();
	return (0);
}