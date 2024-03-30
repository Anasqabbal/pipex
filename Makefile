NAME = pipex
BONUS = pipex_bonus
CC = cc
FLAGS = -Wall -Wextra -g
FILES = pipex.c path.c
FILESB = ft_clear_bonus.c path_bonus.c pipex_bonus.c do_command.c
OFILES = $(FILES:.c=.o)
OFILESB = $(FILESB:.c=.o)
LIB = lib

all : $(LIB) $(NAME)

bonus : $(LIB) $(BONUS)

$(NAME) : $(OFILES)
	$(CC) $(FLAGS) $(OFILES) ./libft/libft.a -o $@

$(BONUS) : $(OFILESB)
	$(CC) $(FLAGS) $(OFILESB) ./libft/libft.a -o $@

%_bonuc.o : %_bonuc.c  pipex_bonuc.h ./libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

%.o : %.c  pipex.h ./libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIB) :
	@$(MAKE) -C ./libft

clean :
	rm -f $(OFILES) $(OFILESB)
	@$(MAKE) -C ./libft $@

fclean :
	rm -f $(NAME) $(BONUS)
	@$(MAKE) -C ./libft $@

re : fclean all
