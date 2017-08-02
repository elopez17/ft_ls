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
CFLAGS	= -Wall -Wextra -Werror
INC		= libft/includes
LIB		= libft.a
EX		= ft_ls

all: $(LIB) $(EX)

$(LIB):
	make -C libft/
	mv libft/libft.a ./

$(EX):
	$(CC) $(CFLAGS) -I $(INC) -c main.c -o main.o
	$(CC) $(CFLAGS) -I $(INC) main.o -L ./ -lft -oft_ls
	./ft_ls

clean:
	rm -f *.o
	make -C libft/ clean

fclean: clean
	rm -f $(LIB)
	rm -f ft_ls
	make -C libft/ fclean

re: fclean all

.PHONY: clean fclean all re

