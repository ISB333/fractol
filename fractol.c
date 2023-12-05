/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:52:57 by adesille          #+#    #+#             */
/*   Updated: 2023/12/05 16:47:57 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

/*
1. Compile with -lm

*/

int main(void)
{
	void    *mlx_ptr;
	void    *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_loop(mlx_ptr);
}
