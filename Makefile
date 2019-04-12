NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -Iincludes/ -Ilibft/includes
LDLIB = -Llibft/
LDFLAGS = -lft
SRCDIR= srcs/
LIB = libft.a
LIBDIR = libft

SRC =	main.c \
		hash/hash_main.c \
		hash/parse_cmd.c \
		hash/process_input.c \
		hash/common.c \
		hash/final.c \
		crypto/md5.c \
		crypto/sha256/sha256.c \
		crypto/sha256/sha256_2.c \
		crypto/sha256/sha256_3.c \
		crypto/sha256/sha224.c \
		crypto/sha512/sha512.c \
		crypto/sha512/sha512_2.c \
		crypto/sha512/sha512_3.c \
		crypto/sha512/sha384.c

SRC := $(addprefix $(SRCDIR), $(SRC))
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(LIBDIR)/$(LIB):
	@$(MAKE) -j8 -C $(LIBDIR)

%.o: %.c includes/ft_ssl.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBDIR)/$(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $(OBJ) $(LDLIB) $(LDFLAGS)

clean:
	rm -f $(OBJ) && $(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME) && $(MAKE) -C $(LIBDIR) fclean

re: fclean $(NAME)

.PHONY: all clean fclean re
