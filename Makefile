# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 10:16:45 by adesille          #+#    #+#              #
#    Updated: 2024/05/22 10:15:45 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = fractol
HEADERS = -I. -I$(LIBMLX)/include -I./libft
CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -ofast -g3
CC = cc

######################## SOURCES ########################

LIBMLX := ./MLX42
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -g3
SRCS := ./srcs/fractol.c ./srcs/complex.c ./srcs/rendering.c \
		./srcs/utils.c ./srcs/utils2.c ./srcs/init.c \
		./srcs/shift.c ./srcs/events.c ./srcs/rendering_utils.c

OBJDIR := .obj
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

######################## RULES ########################

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx