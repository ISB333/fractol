# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 10:16:45 by adesille          #+#    #+#              #
#    Updated: 2024/04/19 15:26:55 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = fractol
HEADERS = -I. -I./include -I$(LIBMLX)/include
DEPFLAGS = -MP -MD
CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -ofast $(DEPFLAGS)
CC = cc

######################## SOURCES ########################

LIBMLX := ./MLX42
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS := ./r_include/fractol.c ./r_include/complex.c ./r_include/rendering.c \
		./r_include/utils.c

OBJDIR := 0_obj
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPFILES := $(SRCS:%.c=$(OBJDIR)/%.d)

GREEN = \033[0;92m
CURRENT_DATE := $(shell date +"%Y-%m-%d %H:%M")

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

######################## RULES ########################

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS)  -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
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

-include $(DEPFILES)

.PHONY: all clean fclean re git libmlx