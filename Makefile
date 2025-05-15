NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c utils.c pipex.c get_command_path.c ft_split_args.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


# test split
split_test: test_split_args.c ft_split_args.o utils.o
	$(CC) $(CFLAGS) -o split_test test_split_args.c ft_split_args.o utils.o
