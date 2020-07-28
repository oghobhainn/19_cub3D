# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmcgahan <cmcgahan@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 15:30:48 by cmcgahan          #+#    #+#              #
#    Updated: 2020/07/28 15:54:00 by cmcgahan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CUB = ./map.cub

MLX = ./mlx/libmlx.a

LIBFT = ./libft/libft.a

SRC = srcs/ft_bmp.c\
	srcs/ft_colors.c\
	srcs/ft_exit.c\
	srcs/ft_init.c\
	srcs/ft_key_press.c\
	srcs/ft_key_press_look.c\
	srcs/ft_key_press_move.c\
	srcs/ft_map.c\
	srcs/ft_parser.c\
	srcs/ft_process.c\
	srcs/ft_resolution.c\
	srcs/ft_sprites.c\
	srcs/ft_textures.c\
	srcs/main.c\
	srcs/utils.c\

BONUS = ./bonus/ft_bmp.c\
	./bonus/ft_colors.c\
	./bonus/ft_exit.c\
	./bonus/ft_init.c\
	./bonus/ft_key_press.c\
	./bonus/ft_key_press_look.c\
	./bonus/ft_key_press_move.c\
	./bonus/ft_map.c\
	./bonus/ft_parser.c\
	./bonus/ft_process.c\
	./bonus/ft_resolution.c\
	./bonus/ft_sprites.c\
	./bonus/ft_textures.c\
	./bonus/main.c\
	./bonus/utils.c\

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

FT_FLAGS = -Wall -Wextra -Werror
FLAGS = -lmlx -framework OpenGL -framework Appkit -L mlx

all:
	@make -C ./mlx
	@make -C ./libft
	@gcc -o $(NAME) -I./ $(FT_FLAGS) $(FLAGS) $(SRC) $(LIBFT) $(MLX)
	@echo "Compilation\t\t\033[0;32m[OK]\033[0m"

clean:
	@make -C ./mlx clean
	@make -C ./libft clean
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)
	@echo "Cleaning Objects\t\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -rf screenshot.bmp
	@echo "Cleaning bmp file\t\t\033[0;32m[OK]\033[0m"
	@rm -rf ${NAME}
	@echo "Cleaning exec\t\t\t\033[0;32m[OK]\033[0m"

bonus: fclean
	@make -C ./mlx
	@make -C ./libft
	@gcc -g -o $(NAME) -I./bonus/ $(FT_FLAGS) $(FLAGS) $(BONUS) $(LIBFT) $(MLX)
	@echo "Compilation Bonus\t\033[0;32m[OK]\033[0m"

re: fclean all

phony: all clean fclean re
