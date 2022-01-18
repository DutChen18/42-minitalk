SRC_CLIENT=client.c
SRC_SERVER=server.c
OBJ_CLIENT=$(SRC_CLIENT:.c=.o)
OBJ_SERVER=$(SRC_SERVER:.c=.o)
CFLAGS=-Wall -Wextra -Werror -Og -g -fsanitize=address
NAME=client server

all: $(NAME)

client: $(OBJ_CLIENT) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^

server: $(OBJ_SERVER) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ $< -c

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C libft clean

fclean: clean
	rm -f client server
	make -C libft fclean

re: fclean all
