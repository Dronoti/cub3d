/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:35:54 by bkael             #+#    #+#             */
/*   Updated: 2022/01/31 12:35:57 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_ray(t_all *all)
{
	double	camera_x;

	camera_x = all->ray.i * 2.0 / (double)WIN_WIDTH - 1.0;
	all->ray.dir.x = all->plr.dir.x + all->plane.x * camera_x;
	all->ray.dir.y = all->plr.dir.y + all->plane.y * camera_x;
	all->map.x = (int)all->plr.pos.x;
	all->map.y = (int)all->plr.pos.y;
	all->ray.delta.x = fabs(1.0 / all->ray.dir.x);
	all->ray.delta.y = fabs(1.0 / all->ray.dir.y);
	all->ray.step_x = 1;
	all->ray.side.x = (all->map.x + 1.0 - all->plr.pos.x) * all->ray.delta.x;
	all->ray.step_y = 1;
	all->ray.side.y = (all->map.y + 1.0 - all->plr.pos.y) * all->ray.delta.y;
	if (all->ray.dir.x < 0)
	{
		all->ray.step_x = -1;
		all->ray.side.x = (all->plr.pos.x - all->map.x) * all->ray.delta.x;
	}
	if (all->ray.dir.y < 0)
	{
		all->ray.step_y = -1;
		all->ray.side.y = (all->plr.pos.y - all->map.y) * all->ray.delta.y;
	}
}

void	ft_run_ray(t_all *all)
{
	int	collision;

	collision = 0;
	while (!collision)
	{
		if (all->ray.side.x < all->ray.side.y)
		{
			all->ray.side.x += all->ray.delta.x;
			all->map.x += all->ray.step_x;
			all->ray.vert_hit = 0;
		}
		else
		{
			all->ray.side.y += all->ray.delta.y;
			all->map.y += all->ray.step_y;
			all->ray.vert_hit = 1;
		}
		if (all->map.map[all->map.y][all->map.x] == '1')
			collision = 1;
	}
}

void	ft_calc_wall(t_all *all)
{
	if (!all->ray.vert_hit)
		all->wall.dist = all->ray.side.x - all->ray.delta.x;
	else
		all->wall.dist = all->ray.side.y - all->ray.delta.y;
	all->wall.height = (int)(WIN_HEIGHT / all->wall.dist);
	all->wall.top = -all->wall.height / 2 + WIN_HEIGHT / 2;
}

void	ft_draw_vert_line(t_all *all)
{
	double	scale;
	int		color;
	int		i;

	scale = 64.0 / (double)all->wall.height;
	all->wall.tex_y = 0;
	i = 0;
	while (i < all->wall.height)
	{
		color = ft_find_texel(all, all->wall.tex_x, (int)all->wall.tex_y);
		my_mlx_pixel_put(all, all->ray.i, all->wall.top + i, color);
		all->wall.tex_y += scale;
		i++;
	}
}

void	ft_draw_scene(t_all *all)
{
	all->ray.i = 0;
	ft_create_floor_ceil(all, all->map.c, 0);
	ft_create_floor_ceil(all, all->map.f, WIN_HEIGHT / 2);
	while (all->ray.i < WIN_WIDTH)
	{
		ft_init_ray(all);
		ft_run_ray(all);
		ft_calc_wall(all);
		ft_find_tex_x(all);
		ft_draw_vert_line(all);
		all->ray.i++;
	}
	ft_minimap(all);
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.win, all->mlx.img, 0, 0);
}
