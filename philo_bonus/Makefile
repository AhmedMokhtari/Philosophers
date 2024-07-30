NAME = philo_bonus

FILES = main.c tool.c

OBJECT = $(FILES:%.c=%.o)

CC = cc

CFLAGS = -g  #-fsanitize=address  -pthread -Wall -Wextra -Werror #-g #-fsanitize=address #-fsanitize=thread 

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

%.o : %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
