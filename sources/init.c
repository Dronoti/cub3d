/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:11:34 by bkael             #+#    #+#             */
/*   Updated: 2022/01/26 12:11:37 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init(t_all *all)
{
	all->mlx.mlx = NULL;
	all->mlx.win = NULL;
	all->mlx.img = NULL;
	all->mlx.addr = NULL;
	all->mlx.bitspp = 0;
	all->mlx.line_l = 0;
	all->mlx.end = 0;
	all->map.map = NULL;
	all->map.height = 0;
	all->map.no = NULL;
	all->map.so = NULL;
	all->map.we = NULL;
	all->map.ea = NULL;
	all->map.f = -1;
	all->map.c = -1;
	all->map.x = 0;
	all->map.y = 0;
	all->plr.pos.x = 0;
	all->plr.pos.y = 0;
	all->plr.dir.x = 0;
	all->plr.dir.y = 0;
	ft_init2(all);
}

void	ft_init2(t_all *all)
{
	all->ray.dir.x = 0;
	all->ray.dir.y = 0;
	all->ray.delta.x = 0;
	all->ray.delta.y = 0;
	all->ray.side.x = 0;
	all->ray.side.y = 0;
	all->ray.step_x = 0;
	all->ray.step_y = 0;
	all->ray.vert_hit = 0;
	all->ray.i = 0;
	all->plane.x = FOV;
	all->plane.y = 0;
	all->wall.height = 0;
	all->wall.top = 0;
	all->wall.tex_x = 0;
	all->wall.tex_y = 0;
	all->wall.dist = 0;
}

void	ft_init_mlx(t_all *all)
{
	all->mlx.mlx = mlx_init();
	if (!all->mlx.mlx)
		ft_free_exit("Error\nMiniLibX error", all);
	all->mlx.win = mlx_new_window(all->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!all->mlx.win)
		ft_free_exit("Error\nMiniLibX error", all);
	all->mlx.img = mlx_new_image(all->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!all->mlx.img)
		ft_free_exit("Error\nMiniLibX error", all);
	all->mlx.addr = mlx_get_data_addr(all->mlx.img, &all->mlx.bitspp,
			&all->mlx.line_l, &all->mlx.end);
	if (!all->mlx.addr)
		ft_free_exit("Error\nMiniLibX error", all);
}
