/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:59:53 by bkael             #+#    #+#             */
/*   Updated: 2022/01/31 17:00:43 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV 0.66
# define SPD_P 0.6
# define SPD_R 0.2
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define LEFT 123
# define RIGHT 124

# include "../utils/get_next_line/get_next_line.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bitspp;
	int		line_l;
	int		end;
}				t_mlx;

typedef struct s_map
{
	char	**map;
	int		height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	int		x;
	int		y;
}				t_map;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_player {
	t_point	pos;
	t_point	dir;
}				t_player;

typedef struct s_ray
{
	t_point	dir;
	t_point	delta;
	t_point	side;
	int		i;
	int		step_x;
	int		step_y;
	int		vert_hit;
}				t_ray;

typedef struct s_wall
{
	int		height;
	int		top;
	int		bottom;
	double	dist;
}				t_wall;

typedef struct s_all
{
	t_mlx		mlx;
	t_map		map;
	t_player	plr;
	t_ray		ray;
	t_point		plane;
	t_wall		wall;
}				t_all;

void	ft_fatal_error(char *msg);
void	ft_free_exit(char *msg, t_all *all);
void	ft_init(t_all *all);
void	ft_init2(t_all *all);
int		ft_is_cub(const char *name);
void	ft_start_parse(t_all *all, char *name);
int		ft_parse_line(t_all *all, char *line);
int		ft_isspace(char c);
int		ft_atoi_ptr(const char *nptr, int *i);
int		ft_parse_map(t_all *all, char *line, int i);
int		ft_check_map_line(char *line, int i);
void	ft_free_arr(char **arr);
int		ft_parse_texture(t_all *all, char **addr, char *line, int i);
int		ft_parse_color(t_all *all, int *addr, char *line, int i);
void	ft_init_mlx(t_all *all);
void	ft_draw_scene(t_all *all);
void	my_mlx_pixel_put(t_all *all, int x, int y, int color);
int		ft_set_position(t_all *all);
void	ft_set_direction(t_all *all, char pov, double i, double k);
int		ft_check_parse(t_all *all);
void	ft_init_ray(t_all *all);
void	ft_run_ray(t_all *all);
void	ft_calc_wall(t_all *all);
void	ft_draw_vert_line(t_all *all);
int		ft_handler_keys(int key, t_all *all);
int		ft_close(t_all *all);
void	ft_move_up_down(int	key, t_all *all);
void	ft_move_left_right(int key, t_all *all);
void	ft_rotation(int key, t_all *all);
void	ft_create_floor_ceil(t_all *all, int color, int start);

#endif
