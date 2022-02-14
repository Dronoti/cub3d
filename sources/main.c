/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:07:32 by bkael             #+#    #+#             */
/*   Updated: 2022/01/22 17:08:58 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc == 2 && ft_is_cub(argv[1]))
	{
		ft_init(&all);
		ft_start_parse(&all, argv[1]);
		ft_init_mlx(&all);
		ft_draw_scene(&all);
		mlx_hook(all.mlx.win, 2, 0, &ft_handler_keys, &all);
		mlx_hook(all.mlx.win, 17, 0, &ft_close, &all);
		mlx_loop(all.mlx.mlx);
		ft_free_exit(NULL, &all);
	}
	else
		ft_fatal_error("Error\nInvalid arguments");
	return (0);
}
