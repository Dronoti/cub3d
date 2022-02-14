/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:58:13 by bkael             #+#    #+#             */
/*   Updated: 2022/01/27 10:58:15 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_set_direction(t_all *all, char pov, double i, double k)
{
	all->plr.pos.x = k + 0.5;
	all->plr.pos.y = i + 0.5;
	if (pov == 'E')
	{
		all->plr.dir.x = 1;
		all->plane.x = 0;
		all->plane.y = FOV;
	}
	else if (pov == 'W')
	{
		all->plr.dir.x = -1;
		all->plane.x = 0;
		all->plane.y = -FOV;
	}
	else if (pov == 'S')
	{
		all->plr.dir.y = 1;
		all->plane.x = -FOV;
	}
	else if (pov == 'N')
		all->plr.dir.y = -1;
}

int	ft_set_position(t_all *all)
{
	double		i;
	double		k;
	char		pov;
	int			count;

	i = -1;
	count = 0;
	while (all->map.map[(int)++i])
	{
		k = -1;
		while (all->map.map[(int)i][(int)++k])
		{
			pov = all->map.map[(int)i][(int)k];
			if (pov == 'N' || pov == 'S' || pov == 'W' || pov == 'E')
			{
				if (count++)
					return (-1);
				ft_set_direction(all, pov, i, k);
				all->map.map[(int)i][(int)k] = '0';
			}
		}
	}
	if (!count)
		return (-1);
	return (0);
}

int	ft_check_map_line(char *line, int i)
{
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E' && !ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_map(t_all *all, char *line, int i)
{
	int		k;
	char	**copy;

	all->map.height++;
	copy = (char **)malloc(sizeof(char *) * (all->map.height + 1));
	if (!copy)
		ft_free_exit("Error\nMalloc error", all);
	copy[all->map.height] = NULL;
	k = -1;
	while (++k < (all->map.height - 1))
		copy[k] = ft_strdup(all->map.map[k]);
	if (ft_check_map_line(line, i))
		copy[k] = ft_strdup(line);
	else
	{
		copy[k] = NULL;
		ft_free_arr(copy);
		return (-1);
	}
	if (all->map.height > 1)
		ft_free_arr(all->map.map);
	all->map.map = copy;
	return (1);
}
