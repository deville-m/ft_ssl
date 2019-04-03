NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Werror -O2
INCLUDES = -Iincludes/ -Ilibft/includes
LDLIB = -Llibft/
LDFLAGS = -lft
SRCDIR= srcs/
LIB = libft.a
LIBDIR = libft

SRC =	main.c \
		parse_cmd.c \
		process_input.c \
		crypto/md5.c \
		crypto/sha256.c

SRC := $(addprefix $(SRCDIR), $(SRC))
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(LIBDIR)/$(LIB):
	@$(MAKE) -j8 -C $(LIBDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBDIR)/$(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $(OBJ) $(LDLIB) $(LDFLAGS)

clean:
	rm -f $(OBJ) && $(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME) && $(MAKE) -C $(LIBDIR) fclean

re: fclean $(NAME)

.PHONY: all clean fclean re
