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

SRC		=	./src/main.c ./src/structure/*.c

CC		=	gcc

CFLAGS	=	-Werror -Wextra -Wall

RDLIB	=	-lreadline

LIB_DIR =	./library/libft/
LIBFT	=	./library/libft/libft.a

BUILD_PRINT = @echo "\e[1;34mminishell created successfully \e[0m"



all:	$(NAME)

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRC) $(RDLIB) $(LIBFT) -o $(NAME)
	$(BUILD_PRINT)


$(LIBFT):
	make -C $(LIB_DIR)
	make clean -C $(LIB_DIR)

clean:
	make fclean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all