NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = src/main.c src/parsing.c src/initialization.c src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all