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

int	ft_check_xpm(const char *line)
{
	int	i;
	int	fd;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
		i++;
	if (i < 5 || line[i - 1] != 'm' || line[i - 2] != 'p' || line[i - 3] != 'x'
		|| line[i - 4] != '.')
		return (-1);
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	ft_parse_texture(t_all *all, char **addr, char *line, int i)
{
	void	*tex;
	int		arg[5];

	if (all->map.map || *addr)
		return (-1);
	while (ft_isspace(*++line))
		i++;
	while (line[i])
		i++;
	while (ft_isspace(line[i - 1]))
		i--;
	if (line[i] != '\0')
		line[i] = '\0';
	if (ft_check_xpm(line))
		return (-1);
	tex = mlx_xpm_file_to_image(all->mlx.mlx, line, &arg[0], &arg[1]);
	if (arg[0] != arg[1] || !tex)
	{
		if (tex)
			mlx_destroy_image(all->mlx.mlx, tex);
		return (-1);
	}
	*addr = mlx_get_data_addr(tex, &arg[2], &arg[3], &arg[4]);
	mlx_destroy_image(all->mlx.mlx, tex);
	return (1);
}

int	ft_parse_color(t_all *all, int *addr, char *line, int i)
{
	int	rgb[3];
	int	j;

	if (all->map.map || *addr != -1)
		return (-1);
	j = 0;
	while (line[j])
	{
		if ((line[j] < '0' || line[j] > '9') && line[j] != '-'
			&& line[j] != ',' && line[j] != '+' && !ft_isspace(line[j]))
			return (-1);
		j++;
	}
	rgb[0] = ft_atoi_ptr(line, &i);
	i++;
	rgb[1] = ft_atoi_ptr(line, &i);
	i++;
	rgb[2] = ft_atoi_ptr(line, &i);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (-1);
	if (line[i] != '\0' || rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (-1);
	*addr = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
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
		return (ft_parse_texture(all, &all->map.no, line + i + 2, i + 2));
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.so, line + i + 2, i + 2));
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.we, line + i + 2, i + 2));
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]))
		return (ft_parse_texture(all, &all->map.ea, line + i + 2, i + 2));
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (ft_parse_color(all, &all->map.f, line + i + 1, i + 1));
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (ft_parse_color(all, &all->map.c, line + i + 1, i + 1));
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
		ft_free_exit("Error\nMap cannot be opened", all);
	ft_init_mlx(all);
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
