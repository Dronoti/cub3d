/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:13:47 by bkael             #+#    #+#             */
/*   Updated: 2022/01/26 11:13:51 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_parse_texture(t_all *all, char **addr, char *line, int i)
{
	if (all->map.map)
		return (-1);
	return (1);
}

int	ft_parse_color(t_all *all, int *addr, char *line, int i)
{
	if (all->map.map)
		return (-1);
	return (1);
}

int	ft_parse_line(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	else if (line[i] == '1')
		return (ft_parse_map(all, line, i));
	else if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.no, line, i));
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.so, line, i));
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.we, line, i));
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.ea, line, i));
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (ft_parse_color(all, &all->map.f, line, i));
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (ft_parse_color(all, &all->map.c, line, i));
	else
		return (-1);
}

void	ft_start_parse(t_all *all, char *name)
{
	char	*line;
	int		fd;
	int		result;

	result = 1;
	line = NULL;
	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_fatal_error("Error\nMap cannot be opened");
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		if (result > 0)
			result = ft_parse_line(all, line);
		if (line)
			free(line);
	}
	close(fd);
	if (result == -1)
		ft_free_exit("Error\nInvalid map", all);
	if (ft_set_position(all) == -1)
		ft_free_exit("Error\nInvalid map", all);
	if (ft_check_parse(all) == -1)
		ft_free_exit("Error\nInvalid map", all);
}
