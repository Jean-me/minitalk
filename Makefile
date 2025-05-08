# minitalk
CLIENT = client
SERVER = server
# SRC
CLIENT_SRC = client.c ft_atoi.c
SERVER_SRC = server.c
# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_PRINTF_DIR = ft_printf
LIB_PRINTF = $(LIB_PRINTF_DIR)/libftprintf.a
# Header
HEADERS = minitalk.h

# Target
all: $(CLIENT) $(SERVER)

# client
$(CLIENT): $(LIB_PRINTF) $(CLIENT_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC) $(LIB_PRINTF)

# server
$(SERVER): $(LIB_PRINTF) $(SERVER_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC) $(LIB_PRINTF)

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