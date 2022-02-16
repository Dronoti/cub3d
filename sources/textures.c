/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:29:01 by bkael             #+#    #+#             */
/*   Updated: 2022/02/16 12:29:04 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_find_tex_x(t_all *all)
{
	double	wall_x;

	if (!all->ray.vert_hit)
		wall_x = all->plr.pos.y + all->wall.dist * all->ray.dir.y;
	else
		wall_x = all->plr.pos.x + all->wall.dist * all->ray.dir.x;
	wall_x -= floor(wall_x);
	all->wall.tex_x = (int)(wall_x * 64.0);
	if ((!all->ray.vert_hit && all->ray.dir.x > 0)
		|| (all->ray.vert_hit && all->ray.dir.y < 0))
		all->wall.tex_x = 64 - all->wall.tex_x - 1;
}

int	ft_find_texel(t_all *all, int x, int y)
{
	int	*tex;

	if (!all->ray.vert_hit)
	{
		if (all->ray.dir.x >= 0)
			tex = all->map.ea;
		else
			tex = all->map.we;
	}
	else
	{
		if (all->ray.dir.y >= 0)
			tex = all->map.so;
		else
			tex = all->map.no;
	}
	return (tex[64 * y + x]);
}

void	ft_copy_texture(int **addr, void *tex_img)
{
	int	arg[3];
	int	*tmp;
	int	i;

	i = 0;
	tmp = (int *)mlx_get_data_addr(tex_img, &arg[0], &arg[1], &arg[2]);
	*addr = (int *)malloc(sizeof(int) * 4096);
	while (i < 4096)
	{
		(*addr)[i] = tmp[i];
		i++;
	}
}
