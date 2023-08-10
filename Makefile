# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 17:57:43 by jcruz-da          #+#    #+#              #
#    Updated: 2023/08/10 16:12:12 by dinoguei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -g #-Werror

RD = -lreadline

SRC = lexer.c

LIBFTDIR = ./libft_group
LIBFT = ./libft_group/libft.a

OBJ = $(SRC:%.c=%.o)

GREEN           :=      \033[1;32m
RED             :=      \033[1;31m
WHITE           :=      \033[1;37m
YELLOW           :=      \033[1;33m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN) [Success] Minishell compilation.$(BOLD)"
	@echo "$(YELLOW) [Success] Libft compilation.$(BOLD)"
	$(MAKE) --no-print-directory -C $(LIBFTDIR)
	@echo "$(YELLOW) [Success] Libft compilation compleated!$(BOLD)"
	$(CC) $(CFLAGS) main.c $(OBJ) $(RD) $(LIBFT) -o $(NAME)
	@echo "$(GREEN) [Success] ./minishell created.$(BOLD)"

clean:
	@rm -rf $(OBJ)
	$(MAKE) clean --no-print-directory -C  $(LIBFTDIR)
	@echo "$(RED) [Deleting] object files deleted.$(BOLD)"

fclean: clean
	@rm -rf $(NAME) $(OBJ)
	$(MAKE) fclean --no-print-directory -C $(LIBFTDIR)
	@echo "$(RED) [Deleting] .a deleted.$(BOLD)"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
