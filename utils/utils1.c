/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 23:32:01 by bkael             #+#    #+#             */
/*   Updated: 2022/01/22 23:32:04 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_fatal_error(char *msg)
{
	if (!msg)
		exit(EXIT_FAILURE);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	ft_free_exit(char *msg, t_all *all)
{
	ft_free_arr(all->map.map);
	if (all->map.no)
		free(all->map.no);
	if (all->map.so)
		free(all->map.so);
	if (all->map.we)
		free(all->map.we);
	if (all->map.ea)
		free(all->map.ea);
	if (all->mlx.img)
		mlx_destroy_image(all->mlx.mlx, all->mlx.img);
	if (all->mlx.win)
		mlx_destroy_window(all->mlx.mlx, all->mlx.win);
	if (msg)
		ft_fatal_error(msg);
	else
		exit(EXIT_SUCCESS);
}

int	ft_close(t_all *all)
{
	ft_free_exit(NULL, all);
	return (0);
}

int	ft_is_cub(const char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (0);
	while (name[i])
		i++;
	if (i >= 5 && name[i - 1] == 'b' && name[i - 2] == 'u' && name[i - 3] == 'c'
		&& name[i - 4] == '.')
		return (1);
	return (0);
}
