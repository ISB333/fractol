# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 10:16:45 by adesille          #+#    #+#              #
#    Updated: 2024/04/15 09:21:43 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = fractol
CFLAGS += -Wall -Wextra -Werror -I.
CC = cc

######################## SOURCES ########################

SRCS = main.c
OBJDIR = 0_obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M")

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = ./MLX42/build/libmlx42.a

######################## RULES ########################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

.PHONY: all clean fclean re git