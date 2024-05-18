# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 10:16:45 by adesille          #+#    #+#              #
#    Updated: 2024/04/21 08:31:59by isb3             ###   ########.fr        #
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

GREEN = \033[0;92m
CURRENT_DATE := $(shell date +"%Y-%m-%d %H:%M")

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
	rm -rf $(OBJDIR) $(DEPFILES)
	rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

.PHONY: all clean fclean re git libmlx