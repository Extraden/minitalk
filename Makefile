CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

LIBFT = libft.a

all: $(SERVER) $(CLIENT)

$(LIBFT):
	make -C libft

$(SERVER): $(LIBFT) server.o
	$(CC) $(CFLAGS) server.o -Llibft -lft -o $(SERVER)

$(CLIENT): $(LIBFT) client.o
	$(CC) $(CFLAGS) client.o -Llibft -lft -o $(CLIENT)

%.o: %.c $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server.o client.o
	make -C libft clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
