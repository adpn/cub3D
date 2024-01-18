# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupin <adupin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 11:21:24 by adupin            #+#    #+#              #
#    Updated: 2024/01/18 13:30:09 by adupin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME 			= 	cub3D

# Compiler, compiler flags and linking flags
CC				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror -Iincludes -Ilibft/include -g 
DFLAGS      	=   -fsanitize=address
MLXFLAGS		=	-lmlx -framework OpenGL -framework AppKit

# Directories for sources files, object files, and the libft library
SRCS_DIR		= 	srcs
PARSER_DIR		=   $(SRCS_DIR)/parser
DISPLAY_DIR		=   $(SRCS_DIR)/display
UTILS_DIR		=	$(SRCS_DIR)/utils
LIBFT_DIR 		= 	libft
BUILD_DIR 		= 	build

# Define the source files
MAIN_FILE		=	main.c
PARSER_FILES	=	cat_all_in_one.c \
					colors.c \
					parser.c \
					split_charset.c \
					conf.c \
					extract_map.c \
					check_map.c
DISPLAY_FILES	=	setup.c \
					display.c \
					mlx_helper.c
UTILS_FILES		=	utils.c

# Defining the paths of the sources files 
SRC_MAIN		= 	$(addprefix $(SRCS_DIR)/,$(MAIN_FILE))
SRC_PARSER  	=	$(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
SRC_DISPLAY 	=	$(addprefix $(DISPLAY_DIR)/, $(DISPLAY_FILES))
SRC_UTILS		=	$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

# Deriving objects from .c files in the build directory
OBJS 			= 	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_MAIN)) \
					$(patsubst $(PARSER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_PARSER)) \
					$(patsubst $(DISPLAY_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_DISPLAY)) \
					$(patsubst $(UTILS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_UTILS)) \

# Display toolbox
RED				=	\x1b[31m
YELLOW			=	\x1b[33m
GREEN			=	\x1b[32m
NO_COLOR		=	\x1b[0m
BOLD			= 	\x1b[1m
BOLD_OFF		=	\x1b[21m

# Rules to build the objects from the sources 
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DISPLAY_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable from the objects and the libft library
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo "$(YELLOW)Linking $(NAME)... $(NO_COLOR)"
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $@ $^
	@echo "$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"

# Rule to build the libft library
$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

# Phony target to build the libft library
libft:
	@make -C $(LIBFT_DIR)

# Phony target to build the libft library and the executable
all: libft $(NAME)

# Phony target to clean the object files
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

# Phony target to remove the executable and build/debug objects
fclean: clean
	@echo "$(RED)Deleting executable...$(NO_COLOR)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf *.dSYM

# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DFLAGS) 
debug: re

# Phony targets for make
.PHONY: all libft clean fclean re debug
