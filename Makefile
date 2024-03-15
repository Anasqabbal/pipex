NAME = pipex
CC = CC 
FLAGS = -Wall -Wextra -Werror
FILES = pipex.c 0_files_and_commands.c the_pipe.c
OFILES = $(FILES:.c=.o)
LIB = lib

all : $(LIB) $(NAME)

$(NAME) : $(OFILES)
	$(CC) $(FLAGS) $(OFILES) ./libft/libft.a -o $@

%.o : %.c  pipex.h ./libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIB) :
	@$(MAKE) -C ./libft

clean :
	rm -f $(OFILES)
	@$(MAKE) -C ./libft $@

fclean :
	rm -f $(NAME)
	@$(MAKE) -C ./libft $@

re : fclean all
