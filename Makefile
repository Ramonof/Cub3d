# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/03 12:41:12 by mrolande          #+#    #+#              #
#    Updated: 2022/09/05 23:41:13 by etobias          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
END = \033[0m

# Key Codes for MacOS
ESC = ESC_KEY=53
W = W_KEY=13
A = A_KEY=0
S = S_KEY=1
D = D_KEY=2
UP = KEY_UP=126
DOWN = KEY_DOWN=125
LEFT = KEY_LEFT=123
RIGHT = KEY_RIGHT=124

SHELL=/bin/bash
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
# 	Key Codes for Linux
	ESC = ESC_KEY=65307
	W = W_KEY=119
	A = A_KEY=97
	S = S_KEY=115
	D = D_KEY=100
	UP = KEY_UP=65362
	DOWN = KEY_DOWN=65364
	LEFT = KEY_LEFT=65361
	RIGHT = KEY_RIGHT=65363
endif

# Keycodes defined during compilation
KEYCODES =  -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

#MAP_SET = -DMAP_SET='" 01NSEW"'

NAME := cub3D
NAME_B := cub3D_bonus
NAME_BONUS := cub3D_bonus
LIBFT := libft/libft.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRC_DIR := ./srcs/
GNL_DIR := ./gnl/
OBJ_DIR	= ./obj/

SRC_FILES = main.c \
			init.c \
			init_utils.c \
			utils.c \
			render.c \
			render_utils.c \
			graphics_utils.c \
			controls.c \
			controls_utils.c \
			errors.c \
			parser.c \
			parse_utils.c \
			parse_utils_utils.c \
			map_parser.c \
			get_map.c \
			check_map.c \
			textures_utils.c \
			free_memory.c \
			sprite_render.c \
			sprite_render_utils.c \
			minimap_render.c

SRC_FILES_B = main.c \
			init.c \
			init_utils.c \
			utils.c \
			render.c \
			render_utils.c \
			graphics_utils.c \
			controls.c \
			controls_utils.c \
			errors.c \
			parser.c \
			parse_utils.c \
			parse_utils_utils.c \
			map_parser_bonus.c \
			get_map.c \
			check_map.c \
			textures_utils.c \
			free_memory.c \
			sprite_render.c \
			sprite_render_utils.c \
			minimap_render.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_GNL_FILES = $(GNL_FILES:.c=.o)
OBJ_FILES_B = $(SRC_FILES_B:.c=.o)

OBJ_D_FILES = $(SRC_FILES:.c=.d)
OBJ_D_GNL_FILES = $(GNL_FILES:.c=.d)
OBJ_D_FILES_B = $(SRC_FILES_B:.c=.d)

SRCS = 	$(addprefix $(SRC_DIR), $(SRC_FILES)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES))

OBJS = 	$(addprefix $(OBJ_DIR), $(OBJ_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_GNL_FILES))

OBJS_D = 	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_GNL_FILES))

SRCS_B = 	$(addprefix $(SRC_DIR), $(SRC_FILES_B)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES))

OBJS_B = 	$(addprefix $(OBJ_DIR), $(OBJ_FILES_B)) \
		$(addprefix $(OBJ_DIR), $(OBJ_GNL_FILES))

OBJS_D_B = 	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES_B)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_GNL_FILES))

HEADER := -I includes/
RM := rm -rf

all: $(NAME)

obj: $(SRCS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(KEYCODES) -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(HEADER) -MMD
	@printf "$(GREEN)█"

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	@$(CC) $(CFLAGS) -O3 -c $< -o $@ $(HEADER) -MMD

$(NAME): echoCMMLX mlx $(LIBFT) echoCM obj $(OBJS) echoCOMP
	@$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT): libft
	@$(MAKE) -s -C ./libft

mlx:
	@$(MAKE) -s -C ./mlx_linux
	@printf "$(GREEN) ---> MLX compilation complete\n"

libft: ;

bonus: $(NAME_B)

$(NAME_B): mlx $(LIBFT) obj $(OBJS_B)
	$(CC) $(OBJS_B) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME_B)

clean:
	@printf "$(CYAN)---> Cleaning obj\n"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean -s -C ./libft

fclean: clean
	@printf "$(CYAN)---> Cleaning executables and libraries\n"
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAME_B)
	@$(MAKE) fclean -s -C ./libft
	@$(MAKE) clean -s -C ./mlx_linux

re: fclean all

-include $(OBJS_D) $(OBJS_D_B)

.PHONY: mlx libft all clean fclean re

echoCM:
	@printf "$(CYAN)---> Compiling Cub3D\n"

echoCMMLX:
	@printf "$(CYAN)---> Compiling MLX\n$(END)"

echoCOMP:
	@printf "$(GREEN) ---> Compilation complete\n"
