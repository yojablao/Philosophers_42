NAME = a.out
head = philo.h
src = main.c pars.c util.c
obj = $(src: %.c=%.o)
CC = cc 
CFLAGE =  -pthread  -fsanitize=thread -g
%.o : %.c $(head)
	CC CFLAGE -c -o $@ $<
all : $(NAME)
	
$(NAME) : $(obj)
	$(CC) $(CFLAGE) -o $@ $(obj)

clean:
	rm -f $(obj) $(NAME)
push:
	git add .
	git commit -m "push"
	git push