NAME = philosophers

INCDIR = INCLUDES
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -pthread
SRCS =	philosophers.c \
		utils.c

OBJS = $(SRCS:.c=.o)

PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

PRINTF_A = $(PRINTF_DIR)/ft_printf.a
GNL_A = $(GNL_DIR)/get_next_line.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(PRINTF_DIR)
	make -C $(GNL_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF_A) $(GNL_A) -o $(NAME)

clean:
	make clean -C $(PRINTF_DIR)
	make clean -C $(GNL_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
