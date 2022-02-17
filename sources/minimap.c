/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:30:42 by bkael             #+#    #+#             */
/*   Updated: 2022/02/17 13:30:45 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_point(t_all *all, int color, int x, int y)
{
	int	start_x;
	int	start_y;

	start_y = y;
	while (start_y < POINT_SIZE + y)
	{
		start_x = x;
		while (start_x < POINT_SIZE + x)
		{
			my_mlx_pixel_put(all, start_x, start_y, color);
			start_x++;
		}
		start_y++;
	}
}

void	ft_minimap(t_all *all)
{
	int	i;
	int	k;
	int	color;

	i = -1;
	while (all->map.map[++i])
	{
		k = -1;
		while (all->map.map[i][++k])
		{
			if (all->map.map[i][k] == '0')
			{
				color = SPACE_COLOR;
				ft_draw_point(all, color, k * POINT_SIZE, i * POINT_SIZE);
			}
			if (all->map.map[i][k] == '1')
			{
				color = WALL_COLOR;
				ft_draw_point(all, color, k * POINT_SIZE, i * POINT_SIZE);
			}
		}
	}
	ft_draw_point(all, PLAYER_COLOR,
		(int)all->plr.pos.x * POINT_SIZE, (int)all->plr.pos.y * POINT_SIZE);
}
