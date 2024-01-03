# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupin <adupin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/24 13:42:57 by alexphil          #+#    #+#              #
#    Updated: 2024/01/03 11:36:08 by adupin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME 		= 	libft.a

# Compiler and compiler flags
CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -Iinclude

# Directories for source files and build directory
BUILD_DIR 	= 	build
LST_DIR 	= 	lists
STR_DIR 	= 	strings
MEM_DIR 	= 	memory

# Define the source files from each directory
LST_SRC 	= 	ft_lstadd_back.c \
		 	  	ft_lstadd_front.c \
			  	ft_lstclear.c \
		  	  	ft_lstdelone.c \
		  	  	ft_lstiter.c \
		      	ft_lstlast.c \
		      	ft_lstmap.c \
		      	ft_lstnew.c \
		      	ft_lstsize.c

STR_SRC 	= 	ft_atoi.c \
		      	ft_isalnum.c \
		      	ft_isalpha.c \
		      	ft_isascii.c \
			  	ft_isdigit.c \
			  	ft_isprint.c \
			  	ft_itoa.c \
		      	ft_putchar_fd.c \
		      	ft_putendl_fd.c \
		      	ft_putnbr_fd.c \
		      	ft_putstr_fd.c \
		      	ft_split.c \
				ft_free_split.c \
		      	ft_strchr.c \
		      	ft_strdup.c \
		      	ft_striteri.c \
		      	ft_strjoin.c \
		      	ft_strlcat.c \
		      	ft_strlcpy.c \
		      	ft_strlen.c \
		      	ft_strmapi.c \
		      	ft_strncmp.c \
		      	ft_strnstr.c \
		      	ft_strrchr.c \
		      	ft_strtrim.c \
		      	ft_substr.c \
		      	ft_tolower.c \
		      	ft_toupper.c

MEM_SRC 	= 	ft_bzero.c \
		  	  	ft_calloc.c \
		  	  	ft_memchr.c \
		  	  	ft_memcmp.c \
		  	  	ft_memcpy.c \
		  	  	ft_memmove.c \
		  	  	ft_memset.c

PRINTF_SRC = 	ft_printf.c utils.c

# Define the path of the sources files from each directory
SRC 		= 	$(addprefix $(LST_DIR)/, $(LST_SRC)) \
	   		  	$(addprefix $(STR_DIR)/, $(STR_SRC)) \
	   		  	$(addprefix $(MEM_DIR)/, $(MEM_SRC))

# Derive object file names from source file names and define the path
OBJS 		= 	$(addprefix $(BUILD_DIR)/, $(LST_SRC:.c=.o)) \
	  		  	$(addprefix $(BUILD_DIR)/, $(STR_SRC:.c=.o)) \
	  		  	$(addprefix $(BUILD_DIR)/, $(MEM_SRC:.c=.o))

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

NO_COLOR		=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(LST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(STR_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(MEM_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the library from object files
$(NAME): $(OBJS)
	@echo "$(YELLOW)Libft ready$(NO_COLOR)"
	@ar rcs $@ $^

# Phony target to build the library
all: $(NAME)

# Phony target to clean the object files
clean:
	@rm -rf $(BUILD_DIR)

# Phony target to delete the library and object files
fclean: clean
	@rm -f $(NAME)

# Phony target to delete the library and object files and rebuild
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

# Phony targets
.PHONY: all clean fclean re
