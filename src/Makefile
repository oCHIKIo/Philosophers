NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c args/args_1.c args/args_2.c time/time.c \
	  monitor/monitor.c print/print_1.c print/print_2.c \
	  routine/routine_1.c routine/routine_2.c routine/routine_3.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
