/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:42 by isb3              #+#    #+#             */
/*   Updated: 2024/05/21 09:15:11 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	show_commands(void)
{
	ft_putstr_fd("\n░▒▓████████▓▒░▒▓███████▓▒░ ░▒▓██████▓▒░ ░▒▓██████▓▒░▒▓██████\
██▓▒░▒▓██████▓▒░░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓██████▓▒░ ░▒▓███████▓▒░░▒▓████████▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░\
░▒▓████████▓▒░ \n\n", 1);
	ft_putstr_fd("Zoom : Scroll\n", 1);
	ft_putstr_fd("Move : Keyboard Arrows\n\n", 1);
	ft_putstr_fd("Change Fractal :\n", 1);
	ft_putstr_fd("Julia 1 = 'J'\n", 1);
	ft_putstr_fd("Julia 2 = 'K'\n", 1);
	ft_putstr_fd("Julia 3 = 'L'\n", 1);
	ft_putstr_fd("Mandelbrot = 'M'\n", 1);
	ft_putstr_fd("Burning Ship = 'B'\n\n", 1);
	ft_putstr_fd("Change colors :\n", 1);
	ft_putstr_fd("Numpad 0 to 5\n", 1);
}

int32_t	main(int argc, char *argv[])
{
	t_data	*d;
	t_coord	*axis;

	if (argc >= 2)
	{
		d = NULL;
		axis = NULL;
		if (parse_coord(&axis, argv))
		{
			if (init_img(&d))
			{
				show_commands();
				d->axis = axis;
				hook_init(d);
				put_pxl(d->image, &axis, d->axis->zoom);
				if (mlx_image_to_window(d->mlx, d->image, 0, 0) == -1)
					return (mlx_close_window(d->mlx), error(), ff(d, axis, 1));
				mlx_loop(d->mlx);
				mlx_delete_image(d->mlx, d->image);
				return (mlx_terminate(d->mlx), ff(d, axis, 0), 0);
			}
		}
		return (command_set("Invalid arguments !\n"), ff(d, axis, 1), 1);
	}
	return (command_set("No arguments given !\n"), 0);
}
