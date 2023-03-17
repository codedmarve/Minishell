# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 18:23:15 by moduwole          #+#    #+#              #
#    Updated: 2023/03/13 18:23:15 by moduwole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRC		=	./src/main.c ./src/start/*.c

CC		=	gcc

CFLAGS	=	-Werror -Wextra -Wall

RDLIB	=	-lreadline

LIB_DIR =	./library/libft/
LIBFT	=	./library/libft/libft.a




all:	$(NAME)

$(NAME): $(SRC) $(LIBFT)
	@$(CC)  $(SRC) $(RDLIB) $(LIBFT) -o $(NAME)
	@echo "minishell created successfully"

$(LIBFT):
	make -C $(LIB_DIR)
	make clean -C $(LIB_DIR)

clean:
	make fclean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all