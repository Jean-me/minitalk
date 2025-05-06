# minitalk
CLIENT = client
SERVER = server
# SRC
CLIENT_SRC = client.c
SERVER_SRC = server.c
# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_PRINTF_DIR = ft_printf
LIB_PRINTF = $(LIB_PRINTF_DIR)/libftprintf.a

# Target
all: $(CLIENT) $(SERVER)

# client
$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC)

# server
$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC)

# $(CLIENT): $(CLIENT_SRC) $(LIB_PRINTF)
# 	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC) $(LIB_PRINTF)

# $(SERVER): $(SERVER_SRC) $(LIB_PRINTF)
# 	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC) $(LIB_PRINTF)

# Library target
$(LIB_PRINTF):
	$(MAKE) -C $(LIB_PRINTF_DIR)

clean:
				rm -f $(CLIENT) $(SERVER)
				$(MAKE) -C $(LIB_PRINTF_DIR) clean

fclean:	clean
				$(RM) $(NAME)
				$(MAKE) -C $(LIB_PRINTF_DIR) fclean

re:		fclean all

.PHONY:	all clean fclean re