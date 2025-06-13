NAME = philosophers

INCDIR = INCLUDES
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -pthread
SRCS =	utils.c \
		philosophers.c

OBJS = $(SRCS:.c=.o)

PRINTF_DIR = ft_printf

PRINTF_A = $(PRINTF_DIR)/ft_printf.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF_A) -o $(NAME)

clean:
	make clean -C $(PRINTF_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
