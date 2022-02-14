# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkael <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 12:11:53 by bkael             #+#    #+#              #
#    Updated: 2022/01/22 19:00:30 by bkael            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

FRAEMWORKS = -framework OpenGL -framework AppKit

MLX = mlx/libmlx.a

HEADER = includes/cub3d.h

SRC = sources/main.c \
	sources/parser.c \
	sources/parse_map.c \
	sources/init.c \
	sources/handler_keys.c \
	sources/check_parse.c \
	sources/draw_scene.c \
	utils/utils1.c \
	utils/utils2.c \
	utils/get_next_line/get_next_line.c \
	utils/get_next_line/get_next_line_utils.c

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C mlx/
	gcc $(FLAGS) $^ $(MLX) $(FRAEMWORKS) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C mlx/ clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
