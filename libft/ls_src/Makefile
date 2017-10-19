NAME		= ../libft.a
EX			= ../../ft_ls
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g
FILES		= $(shell ls | grep -E ".+\.c")
ODIR		:= obj
OBJ			:= $(addprefix $(ODIR)/,$(FILES:%.c=%.o))
#-fsanitize=address -fno-omit-frame-pointer
all: $(NAME) $(EX)


$(EX): $(OBJ)
	$(CC) $(CFLAGS) -I ../../includes $(OBJ) -L ../ -lft -oft_ls
	mv ft_ls ../../

$(NAME):
	make -C ../

$(ODIR)/%.o:%.c | $(ODIR)
	$(CC) $(CFLAGS) -I ../../includes -o $@ -c $<

$(ODIR):
	mkdir $(ODIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(EX)

re: fclean all

.PHONY: clean fclean all re
