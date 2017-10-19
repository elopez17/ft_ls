NO_COLOR= \x1b[0m
B_GRY	= \x1b[30;01m
B_RED	= \x1b[31;01m
B_GRN	= \x1b[32;01m
B_YEL	= \x1b[33;01m
B_BLU	= \x1b[34;01m
B_PURP	= \x1b[35;01m
B_TURQ	= \x1b[36;01m
B_WHT	= \x1b[37;01m
GRY		= \x1b[30m
RED		= \x1b[31m
GRN		= \x1b[32m
YEL		= \x1b[33m
BLU		= \x1b[34m
PURP	= \x1b[35m
TURQ	= \x1b[36m
WHT		= \x1b[37m

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
INC		= includes
LIB		= libft/libft.a
NAME	= ft_ls
#-fsanitize=address -fno-omit-frame-pointer
all: $(NAME)

$(NAME): $(LIB)
	make -C libft/ls_src/

$(LIB):
	make -C libft/

clean:
	rm -f *.o
	make -C libft/ clean
	make -C libft/ls_src/ clean

fclean: clean
	make -C libft/ fclean
	make -C libft/ls_src/ fclean

re: fclean all

.PHONY: clean fclean all re

