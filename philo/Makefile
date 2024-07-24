NAME = philo

FILES = main.c init.c tool.c mutex_set_ret.c tool1.c philo_op.c

OBJECT = $(FILES:%.c=%.o)

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror -g -fsanitize=address #-fsanitize=thread 

all : $(NAME)

$(NAME) : $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
