NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS_DIR	= src
OBJ_DIR		= .obj

vpath %.c $(SRCS_DIR)
vpath %.h includes

SRCS_FILES	= main.c \
              parsing.c \
              cleanup.c \
              initialization.c \
              utils.c \
              routine.c \
              simulation.c

HEADER_FILES = philo.h

OBJS		= $(SRCS_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re