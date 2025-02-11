CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

LIBFT = libft.a

all: $(SERVER) $(CLIENT)

$(LIBFT):
	make -C libft

$(SERVER): server.o | $(LIBFT)
	$(CC) $(CFLAGS) server.o -L./libft -lft -o $(SERVER)

$(CLIENT): client.o | $(LIBFT)
	$(CC) $(CFLAGS) client.o -L./libft -lft -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server.o client.o
	make -C libft clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
