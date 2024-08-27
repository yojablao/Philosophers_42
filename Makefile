NAME = philo
head = philo.h
src = main.c pars.c util.c action.c
obj = $(src:%.c=%.o)
CC = cc 
CFLAGE = -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

%.o : %.c $(head)
	$(CC) $(CFLAGE) -c -o $@ $<
all : $(NAME)

$(NAME) : $(obj)
	$(CC) $(CFLAGE) -o $@ $(obj)

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(NAME)

re: fclean all

push:
	git add .
	git commit -m "yojablao"
	git push