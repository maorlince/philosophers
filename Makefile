NAME = philo

INCDIR = INCLUDES
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -pthread -g3
SRCS =	utils.c \
		routine.c \
		philosophers.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
