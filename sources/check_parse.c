/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:40:32 by bkael             #+#    #+#             */
/*   Updated: 2022/01/31 18:40:34 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_space(t_all *all, int i, int j)
{
	if (i == 0 || all->map.map[i][j] == 0)
		return (-1);
	if (j == 0 || all->map.map[i + 1] == 0)
		return (-1);
	if (all->map.map[i - 1][j] == ' ' || all->map.map[i - 1][j] == '\0')
		return (-1);
	if (all->map.map[i + 1][j] == ' ' || all->map.map[i + 1][j] == '\0')
		return (-1);
	if (all->map.map[i][j - 1] == ' ' || all->map.map[i][j - 1] == '\0')
		return (-1);
	if (all->map.map[i][j + 1] == ' ' || all->map.map[i][j + 1] == '\0')
		return (-1);
	return (0);
}

int	ft_check_parse(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map.map[i] != 0)
	{
		j = 0;
		while (all->map.map[i][j] != 0)
		{
			if (all->map.map[i][j] == '0')
			{
				if (ft_check_space(all, i, j) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
