# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zrz <zrz@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 17:02:20 by fmaurer           #+#    #+#              #
#    Updated: 2025/03/26 17:40:23 by zrz              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

SRC_DIR     =   ./src

# --- Platform Detection ---
ARCH := $(shell uname -m)
IS_FEDORA := $(shell test -f /etc/fedora-release && echo 1)
# Check for common ARM identifiers
IS_ARM := $(findstring arm,$(ARCH))$(findstring aarch64,$(ARCH))

# --- Conditional MLX Setup ---
# Default to minilibx-linux
MLX_TARGET_DIR := ./minilibx-linux
MLX_LIBS := -lmlx -lXext -lX11

# Use OpenGL version for ARM or Fedora
USE_OPENGL := 0
ifneq ($(IS_ARM),)
	USE_OPENGL := 1
endif
ifeq ($(IS_FEDORA),1)
	USE_OPENGL := 1
endif

ifeq ($(USE_OPENGL),1)
	MLX_TARGET_DIR := ./minilibx_opengl # Ensure this matches the unpacked directory name
	# Common libs for mlx_opengl. Adjust if needed. Requires OpenGL development libraries installed.
	MLX_LIBS := -lmlx -lGL -lGLU -lXext -lX11
   # @echo "Using MiniLibX OpenGL for $(ARCH) / Fedora=$(IS_FEDORA)"
else
   # @echo "Using MiniLibX Linux (X11) for $(ARCH) / Fedora=$(IS_FEDORA)"
endif
# --- End Conditional MLX Setup ---

# using the *magic* VPATH variable for finding my sources 🤯. also possible to
# use it like: `vpath %.c dir1/ dir2/ ...`. more on this ->
# https://makefiletutorial.com/#the-vpath-directive
#
# TLDR; this will make make find the correct source file `./src/exec/bla.c` for
# any ob called `ob/bla.o`
VPATH	=	./src ./src/linalg ./src/objects ./src/ui ./src/utils ./src/raytrace \
				./src/parsing ./src/xpm ./src/setup_scene

# list all source files here
SRCS		=	main.c \
					parse_scene.c \
					close_btn_handler.c \
					init_mrt.c \
					kbd_input_handler.c \
					kbd_handle_fov_sub.c \
					rgb_to_int_tcolr.c \
					vec3_new.c \
					vec3_basic_ops.c \
					vec3_products.c \
					v3_new.c \
					v3_basic_ops.c \
					v3_advanced_ops.c \
					mtrx_ops.c \
					mtrx_new_print.c \
					get_rotmtrx.c \
					put_pixel_string.c \
					sidebar.c \
					sidebar_print_text.c \
					ui-utils.c \
					objlst.c \
					objlst_print.c \
					print_scene.c \
					tcolr_to_int.c \
					raytrace.c \
					math_utils.c \
					get_object_colr.c \
					intersect_ray_obj.c \
					sphere_intersect.c \
					sphere_colr.c \
					calculate_lights.c \
					colr_utils.c \
					do_stuff.c \
					general_utils.c \
					parser.c \
					parser_objs.c \
					parser_objs2.c \
					parser_parse.c \
					parser_utils.c \
					parser_utils2.c \
					ft_atof.c \
					tokenizer.c \
					tokenizer_next.c \
					tokenizer_nums.c \
					setup_init_scene.c \
					raytrace_xpm.c \
					xpm.c \
					cleanup_mrt.c \
					kbd_cam.c \
					cam_get_new_pos_rot.c


OBJDIR  =   obj
OBJS        =   $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

LIBFT_PATH  = ./libft
LIBFT               = $(LIBFT_PATH)/libft.a

# Use the conditionally set MLX directory
LIBMLX_PATH = $(MLX_TARGET_DIR)
LIBMLX          = $(MLX_TARGET_DIR)/libmlx.a # Assuming library name is still libmlx.a inside

# Use the conditionally set MLX directory and libs
LIB_PATHS = -L$(MLX_TARGET_DIR) -L$(LIBFT_PATH)
LIBS            = $(MLX_LIBS) -lm -lft # Use MLX_LIBS determined above

INC_DIR         = $(SRC_DIR)/include
# Use the conditionally set MLX directory for includes
INC                 = -I$(INC_DIR) -I$(MLX_TARGET_DIR) -I$(LIBFT_PATH)

MINRT_HDRS	= $(INC_DIR)/minirt.h \
							$(INC_DIR)/vec3.h \
							$(INC_DIR)/v3.h \
							$(INC_DIR)/constants.h \
							$(INC_DIR)/objects.h \
							$(INC_DIR)/mtrx.h \
							$(INC_DIR)/parser.h

# change this back to 'cc' @school for eval
CC			=	clang
CFLAGS	=	-g -Werror -Wall -Wextra

# special nix compilation support for mlx. see LIBMLX rule.
NIX11 = $(shell echo $$NIX11)

# GRN = \033[0;32m
GRN = \033[38;5;40m
RED = \033[1;31m
WHT = \033[1;37m
EOC = \033[1;0m
# YLW = \033[1;33m
YLW = \033[38;5;3m
MSGOPN = $(YLW)[[$(GRN)
MSGEND = $(YLW)]]$(EOC)

log_msg = $(MSGOPN) $(1) $(MSGEND)

# Control preproc consts in constants.h based on build host:
ifeq ($(HOST), rubi)
	BHOST = RUBI
else
	BHOST = DEFAULT
endif

all: $(NAME)

$(OBJDIR)/%.o : %.c $(MINRT_HDRS)
	@mkdir -p $(OBJDIR)
	@echo -e "$(call log_msg,Compiling: $<)"
	@$(CC) -D$(BHOST) $(CFLAGS) $(INC) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	@echo -e "$(call log_msg,Compiling minirt...)"
	$(CC) -D$(BHOST) $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	@echo -e "$(call log_msg,Compiling libft...)"
	make -C $(LIBFT_PATH) all

$(LIBMLX):
	@echo -e "$(call log_msg,Compiling MLX in $(MLX_TARGET_DIR)...)"
ifeq ($(USE_OPENGL),1)
	# Compile OpenGL version - Assuming 'make' in its directory works
	# You might need specific flags or steps depending on the OpenGL version's requirements
	@echo -e "$(call log_msg,Compiling MLX OpenGL version...)"
	@make -C $(MLX_TARGET_DIR)/
else
	# Compile Linux X11 version (original logic)
	@echo -e "$(call log_msg,Compiling MLX Linux X11 version...)"
	ifdef NIX11
		@echo -e "$(call log_msg,feels nixy around here.. Compiling MLX the nix way!)"
		# Apply Nix-specific patches only for the linux version
		sed -i 's/local xlib_inc="$$(get_xlib_include_path)"/local xlib_inc="$$NIX11"/g' $(MLX_TARGET_DIR)/configure || true
		sed -i 's/mlx_int_anti_resize_win/\/\/mlx_int_anti_resize_win/g' $(MLX_TARGET_DIR)/mlx_new_window.c || true
		NIX11=$(NIX11) make -C $(MLX_TARGET_DIR)/
	else
		@echo -e "$(call log_msg,feels clustery around here.. compiling MLX the normal way!)"
		@make -C $(MLX_TARGET_DIR)/
	endif
endif

bonus: $(NAME)

mlx: $(LIBMLX)

debug: $(SRCS) $(LIBFT) $(LIBMLX) $(MINRT_HDRS)
	$(CC) -g $(CFLAGS) $(INC) $(LIB_PATHS) -o $(NAME) $(SRCS) $(LIBS)

setup:
	@echo -e "$(call log_msg,Setting things up...)"
	@rm -rf ./minilibx-linux ./test_maps
	@echo -e "$(call log_msg,Downloading mlx...)"
	@wget -c https://cdn.intra.42.fr/document/document/31543/minilibx-linux.tgz 2> /dev/null
	@wget -c https://cdn.intra.42.fr/document/document/31544/minilibx_opengl.tgz 2> /dev/null
	@echo	-e "$(call log_msg,Unpacking mlx...)"
	@tar xzf ./minilibx-linux.tgz > /dev/null
	@tar xzf ./minilibx_opengl.tgz > /dev/null
	@echo	-e "$(call log_msg,Cloning libft submodule...)"
	@git submodule update --init
	@sleep 1s
	@echo -e "$(call log_msg,There you go!)"

fullclean:
	@echo -e "$(call log_msg,Removing libft objs.)"
	@make -s -C $(LIBFT_PATH) clean
	@echo -e "$(call log_msg,Removing libmlx objs from $(MLX_TARGET_DIR).)" # Updated path
	@make -s -C $(MLX_TARGET_DIR) clean # Use variable
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

clean:
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)

fullfclean:
	@echo -e "$(call log_msg,fcleaning libft.)"
	@make -s -C $(LIBFT_PATH) fclean
	@echo -e "$(call log_msg,fcleaning libmlx from $(MLX_TARGET_DIR).)" # Updated path
	@make -s -C $(MLX_TARGET_DIR) clean # Use variable (mlx usually only has 'clean')
	@echo -e "$(call log_msg,Removing minirt objs.)"
	@rm -rf $(OBJDIR)
	@echo -e "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)

fclean: clean
	@echo -e "$(call log_msg,Removing $(NAME) binary.)"
	@rm -f $(NAME)


fullre: fullfclean all

re: fclean all

.PHONY: all fullclean clean fclean re mlx debug bonus setup help
