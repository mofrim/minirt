# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2025/03/03 14:04:33 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

SRCS_IN = ./main.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

OBJS_DIR = obj
OBJS	= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS)) 

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

LIBMLX_PATH = ./minilibx-linux
LIBMLX = ./minilibx-linux/libmlx.a

LIB_PATHS = -L$(LIBMLX_PATH) -L$(LIBFT_PATH)
LIBS = -lmlx -lXext -lX11 -lm -lft

MINRT_HDR	= minirt.h
INC = -I$(LIBMLX_PATH) -I$(LIBFT_PATH)

CC = clang
CFLAGS	=	-Werror -Wall -Wextra

# special nix compilation support for mlx. see LIBMLX rule.
NIX11 = $(shell echo $$NIX11)

GRN = \033[1;32m
RED = \033[1;31m
WHT = \033[1;37m
EOC = \033[1;0m
YLW = \033[1;33m
MSGOPN = $(YLW)[[$(GRN)
MSGEND = $(YLW)]]$(EOC)

log_msg = $(MSGOPN) $(1) $(MSGEND)

all: $(NAME)

$(OBJS_DIR)/%.o : %.c $(MINRT_HDR)
	@mkdir -p $(OBJS_DIR)
	@echo -e "$(call log_msg,Compiling: $<)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@echo -e "$(call log_msg,Compiling minirt...)"
	$(CC) $(CFLAGS) $(INC) $(LIB_PATHS) -o fdf $(OBJS) $(LIBS)

$(LIBFT):
	@echo -e "$(call log_msg,Compiling libft...)"
	make -C $(LIBFT_PATH) all

$(LIBMLX):
ifdef NIX11
	@echo -e "$(call log_msg,feels nixy around here.. Compiling MLX the nix way!)"
	sed -i 's/local xlib_inc="$$(get_xlib_include_path)"/local xlib_inc="$$NIX11"/g' ./minilibx-linux/configure 
	sed -i 's/mlx_int_anti_resize_win/\/\/mlx_int_anti_resize_win/g' ./minilibx-linux/mlx_new_window.c
	# sed -i 's/# define WINX 2000/# define WINX 1400/g' ./fdf.h
	# sed -i 's/# define WINY 1500/# define WINY 1000/g' ./fdf.h
	NIX11=$NIX11 make -C ./minilibx-linux/
else
	@echo -e "$(call log_msg,feels clustery around here.. compiling MLX the normal way!)"
	@echo
	make -C ./minilibx-linux/
endif

bonus: $(NAME)

mlx: $(LIBMLX)

debug: $(SRCS) $(LIBFT) $(LIBMLX) $(MINRT_HDR)
	$(CC) -g $(CFLAGS) $(INC) $(LIB_PATHS) -o fdf $(SRCS) $(LIBS)

setup:
	@echo -e "$(call log_msg,Setting things up...)"
	@rm -rf ./minilibx-linux ./test_maps
	@echo -e "$(call log_msg,Downloading mlx...)"
	@wget -c https://cdn.intra.42.fr/document/document/30844/minilibx-linux.tgz 2> /dev/null
	@wget -c https://cdn.intra.42.fr/document/document/30845/minilibx_opengl.tgz 2> /dev/null
	@echo	-e "$(call log_msg,Unpacking mlx...)"
	@tar xzf ./minilibx-linux.tgz > /dev/null
	@tar xzf ./minilibx_opengl.tgz > /dev/null
	@sleep 1s
	@echo -e "$(call log_msg,There you go!)"

clean: 
	@echo -e "$(call log_msg,Removing libft objs.)"
	@make -s -C $(LIBFT_PATH) clean
	@echo -e "$(call log_msg,Removing libmlx objs.)"
	@make -s -C $(LIBMLX_PATH) clean
	@echo -e "$(call log_msg,Removing fdf objs.)"
	@rm -rf $(OBJS_DIR)

fclean:
	@echo -e "$(call log_msg,fcleaning libft.)"
	@make -s -C $(LIBFT_PATH) fclean
	@echo -e "$(call log_msg,fcleaning libmlx.)"
	@make -s -C $(LIBMLX_PATH) clean
	@echo -e "$(call log_msg,Removing fdf objs.)"
	@rm -rf $(OBJS_DIR)
	@echo -e "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx debug bonus setup help
