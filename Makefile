NAME := cub3D
LIBFT := libft/libft.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRC_DIR := ./srcs/
GNL_DIR := ./gnl/
OBJ_DIR	= ./obj/

SRC_FILES = main.c \
			render.c \
			graphics_utils.c \
			controls.c \
			utils.c \
			errors.c \
			parser.c \
			textures_utils.c \
			init.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_GNL_FILES = $(GNL_FILES:.c=.o)

OBJ_D_FILES = $(SRC_FILES:.c=.d)
OBJ_D_GNL_FILES = $(GNL_FILES:.c=.d)

SRCS = 	$(addprefix $(SRC_DIR), $(SRC_FILES)) \
		$(addprefix $(GNL_DIR), $(GNL_FILES))

OBJS = 	$(addprefix $(OBJ_DIR), $(OBJ_FILES)) \
		$(addprefix $(OBJ_DIR), $(OBJ_GNL_FILES))

OBJS_D = 	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES)) \
			$(addprefix $(OBJ_DIR), $(OBJ_D_GNL_FILES))

HEADER := -I includes/
RM := rm -rf

all: $(NAME)

obj: $(SRCS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ $(HEADER) -MMD
	@printf "$(GREEN)█"

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	@$(CC) $(CFLAGS) -O3 -c $< -o $@ $(HEADER) -MMD

$(NAME): echoCMMLX mlx $(LIBFT) echoCM obj $(OBJS) echoCOMP
	@$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT): libft
	@$(MAKE) -s -C ./libft

mlx:
	@$(MAKE) -s -C ./mlx_linux
	@echo "$(GREEN) ---> MLX compilation complete\n"

libft: ;

bonus: $(NAME)

clean:
	@echo "$(CYAN)---> Cleaning obj\n"
	@$(RM) $(OBJ_DIR)
	@$(MAKE) clean -s -C ./libft

fclean: clean
	@echo "$(CYAN)---> Cleaning executables and libraries\n"
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -s -C ./libft
	@$(MAKE) clean -s -C ./mlx_linux

re: fclean all

-include $(OBJS_D)

.PHONY: mlx libft all clean fclean re

echoCM:
	@echo "$(CYAN)---> Compiling Cub3D"

echoCMMLX:
	@echo "$(CYAN)---> Compiling MLX$(END)"

echoCOMP:
	@echo "$(GREEN) ---> Compilation complete\n"

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
END = \033[0m