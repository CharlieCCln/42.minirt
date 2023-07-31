# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:33:09 by ccrottie          #+#    #+#              #
#    Updated: 2023/07/31 15:23:32 by ccrottie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

INC_DIR		=	./incs/
INC			=	minirt.h

HEADERS		=	$(addprefix $(INC_DIR), $(INC))

LIBFT_DIR	=	libft/
LIBFT_A		=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	libft

MLX_DIR		=	minilibx-linux/
MLX_A		=	$(MLX_DIR)libmlx_Linux.a
MLX_INC		=	minilibx-linux

SRC_DIR		=	./srcs/
SRC			=	main.c \
				parsing/arg_check.c \
				parsing/parsing_hub.c \
				parsing/gnl_safe.c \
				parsing/check_unique_element.c \
				parsing/parse_filename.c \
				memory/init.c \
				memory/terminate.c

OBJ_DIR		=	objs/
OBJ			=	$(SRC:%.c=$(OBJ_DIR)%.o)

CC			=	cc
CC_FLAGS	=	-Wextra -Werror -Wall -O3 -g3

all: 			build_libft build_mlx $(NAME)

$(OBJ): 		$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) $(LIBFT_A) $(LIBFT_DIR)libft.h $(MLX_A) $(MLX_DIR)mlx.h
				mkdir -p $(@D)
				$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_INC) -c $< -o $@

$(NAME):		$(OBJ) $(MLX_A)
				$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT_A) $(MLX_A) -lXext -lX11 -lm -lz -o $@

build_libft:
				$(MAKE) -C $(LIBFT_DIR)

build_mlx:
				$(MAKE) -C $(MLX_DIR)
	
clean:
				$(MAKE) -C $(LIBFT_INC) fclean
				$(MAKE) -C $(MLX_INC) clean
				rm -rf $(OBJ_DIR)

fclean: 		clean
				rm -rf $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re