/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:22:13 by bkael             #+#    #+#             */
/*   Updated: 2022/01/27 14:22:23 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = all->mlx.addr + (y * all->mlx.line_l + x * (all->mlx.bitspp / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	long long		num;
	long long		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		if (num > 2147483647 && sign == 1)
			return (-1);
		if (num > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (num * sign);
}

void	ft_create_floor_ceil(t_all *all, int color, int start)
{
	int	i;
	int	k;

	i = 0;
	while (i < (WIN_HEIGHT / 2))
	{
		k = 0;
		while (k < WIN_WIDTH)
		{
			my_mlx_pixel_put(all, k, start + i, color);
			k++;
		}
		i++;
	}
}
