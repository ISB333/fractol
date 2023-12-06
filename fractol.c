/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:52:57 by adesille          #+#    #+#             */
/*   Updated: 2023/12/06 17:56:14 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

/*
1. Compile with -lm

*/

int	deal_key(int key, void *param)
{
	printf("%c\n", 'X');
	return(0);
}

int main(void)
{
	void    *mlx_ptr;
	void    *win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	if (!win_ptr)
		return(free(win_ptr), 1);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr); // loop that let the graphic server works
   	mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
}

// lmlx -lXext -lX11