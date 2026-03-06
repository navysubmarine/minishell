CC      = cc
CFLAGS  = -Wall -Wextra -Werror
NAME    = libftprintf.a

SOURCES = ft_printf.c utils_gen.c utils_if.c \
          utils_putnbr.c utils_putnbr_base.c

OBJETS  = $(SOURCES:.c=.o)
LIBFT   = ../libft/libft.a

# Include path
INCLUDES = -Iincludes -I../libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJETS) $(LIBFT)
	ar rcs $(NAME) $(OBJETS)

$(LIBFT):
	@$(MAKE) -C ../libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJETS)

fclean: clean
	rm -f $(NAME)

re: fclean all