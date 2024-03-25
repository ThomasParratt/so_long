# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 15:02:48 by tparratt          #+#    #+#              #
#    Updated: 2024/03/15 16:34:27 by tparratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long

SRC         = main.c valid_map.c utils.c valid_path.c move_player.c init_game.c
OBJ         = $(SRC:.c=.o)

LIBFT       = libft/libft.a

MLX42_DIR   = ./MLX42
MLX42_LIBS  = $(MLX42_DIR)/build/libmlx42.a -L ~/.brew/opt/glfw/lib -lglfw -ldl -pthread -lm

CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror -Wunreachable-code
OPT_FLAGS   = -Ofast

$(NAME): $(OBJ)
	make -C ./libft
	cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	make -C $(MLX42_DIR)/build -j4
	$(CC) $(CFLAGS) $(OPT_FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX42_LIBS)

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJ)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
	$(RM) -r $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re
