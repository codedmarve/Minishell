NAME	=	minishell

SRC		=	./src/main.c ./src/parsing/*.c ./src/env_init/*.c \
			./src/cmdGroup_init/*.c  ./src/execution/*.c  ./src/builtins/*.c \

CC		=	gcc

CFLAGS	=	-g -Werror -Wextra -Wall

RDLIB	=	-lreadline

LIB_DIR =	./library/libft/
LIBFT	=	./library/libft/libft.a

all:	$(NAME)

$(NAME): $(SRC) $(LIBFT)
	@$(CC)  $(SRC) $(RDLIB) $(LIBFT) -o $(NAME)
	@echo "minishell created successfully"

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@make clean -C $(LIB_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@rm -rf $(NAME)

re: fclean all