BONUS = pipex
CC = cc
FILE = ../.mand
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
BFILES = pipex_bonus.c path_bonus.c exec_bonus.c
BOFILES =  $(BFILES:_bonus.c=_bonus.o)
LIB = lib

all :  file $(LIB) $(BONUS)



$(BONUS) : $(BOFILES)
	$(CC) $(FLAGS) $(BOFILES) ./libft/libft.a -o $@
	@cp $@ ..
	@touch .bon

%_bonus.o : %_bonus.c pipex_bonus.h ./libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIB) :
	@$(MAKE) -C ./libft

clean :
	rm -f $(BOFILES)
	@$(MAKE) -C ./libft $@

fclean : clean
	rm -f $(BONUS)
	@$(MAKE) -C ./libft $@

re : fclean all