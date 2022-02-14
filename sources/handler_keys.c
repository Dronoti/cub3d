/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:10:51 by bkael             #+#    #+#             */
/*   Updated: 2022/02/10 12:10:54 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_move_up_down(int key, t_all *all)
{
	if (key == KEY_W)
	{
		if (all->map.map[(int)(all->plr.pos.y)]
			[(int)(all->plr.pos.x + all->plr.dir.x * SPD_P)] == '0')
			all->plr.pos.x += all->plr.dir.x * SPD_P;
		if (all->map.map[(int)(all->plr.pos.y + all->plr.dir.y * SPD_P)]
			[(int)(all->plr.pos.x)] == '0')
			all->plr.pos.y += all->plr.dir.y * SPD_P;
	}
	if (key == KEY_S)
	{
		if (all->map.map[(int)(all->plr.pos.y)]
			[(int)(all->plr.pos.x - all->plr.dir.x * SPD_P)] == '0')
			all->plr.pos.x -= (all->plr.dir.x * SPD_P);
		if (all->map.map[(int)(all->plr.pos.y - all->plr.dir.y * SPD_P)]
			[(int)(all->plr.pos.x)] == '0')
			all->plr.pos.y -= (all->plr.dir.y * SPD_P);
	}
	ft_draw_scene(all);
}

void	ft_move_left_right(int key, t_all *all)
{
	if (key == KEY_D)
	{
		if (all->map.map[(int)(all->plr.pos.y)]
			[(int)(all->plr.pos.x + all->plane.x * SPD_P)] == '0')
			all->plr.pos.x += all->plane.x * SPD_P;
		if (all->map.map[(int)(all->plr.pos.y + all->plane.y * SPD_P)]
			[(int)(all->plr.pos.x)] == '0')
			all->plr.pos.y += all->plane.y * SPD_P;
	}
	if (key == KEY_A)
	{
		if (all->map.map[(int)(all->plr.pos.y)]
			[(int)(all->plr.pos.x - all->plane.x * SPD_P)] == '0')
			all->plr.pos.x -= all->plane.x * SPD_P;
		if (all->map.map[(int)(all->plr.pos.y - all->plane.y * SPD_P)]
			[(int)(all->plr.pos.x)] == '0')
			all->plr.pos.y -= all->plane.y * SPD_P;
	}
	ft_draw_scene(all);
}

void	ft_rotation(int key, t_all *all)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = all->plr.dir.x;
	old_planex = all->plane.x;
	if (key == LEFT)
	{
		all->plr.dir.x = all->plr.dir.x * cos(-SPD_R)
			- all->plr.dir.y * sin(-SPD_R);
		all->plr.dir.y = old_dirx * sin(-SPD_R) + all->plr.dir.y * cos(-SPD_R);
		all->plane.x = all->plane.x * cos(-SPD_R) - all->plane.y * sin(-SPD_R);
		all->plane.y = old_planex * sin(-SPD_R) + all->plane.y * cos(-SPD_R);
	}
	if (key == RIGHT)
	{
		all->plr.dir.x = all->plr.dir.x * cos(SPD_R)
			- all->plr.dir.y * sin(SPD_R);
		all->plr.dir.y = old_dirx * sin(SPD_R) + all->plr.dir.y * cos(SPD_R);
		all->plane.x = all->plane.x * cos(SPD_R) - all->plane.y * sin(SPD_R);
		all->plane.y = old_planex * sin(SPD_R) + all->plane.y * cos(SPD_R);
	}
	ft_draw_scene(all);
}

int	ft_handler_keys(int key, t_all *all)
{
	if (key == ESC)
		ft_free_exit(NULL, all);
	else if (key == KEY_W || key == KEY_S)
		ft_move_up_down(key, all);
	else if (key == KEY_A || key == KEY_D)
		ft_move_left_right(key, all);
	else if (key == LEFT || key == RIGHT)
		ft_rotation(key, all);
	return (0);
}
