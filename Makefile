NAME = pipex
CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

SRC = 	main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) -o $@ 

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(FLAGS) -c $^

clean:
	make fclean -C libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	./pipex input "grep fd" "wc -l" output

.PHONY = clean fclean re
