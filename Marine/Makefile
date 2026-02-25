CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3
NAME    = minishell

INCLUDE_DIRS = -Iincludes -Iincludes/ft_printf -Iincludes/libft

SOURCES = minishell.c cmd.c

OBJETS  = $(SOURCES:.c=.o)

FTPRINTF_DIR = includes/ft_printf
LIBFT_DIR    = includes/libft

FTPRINTF = includes/ft_printf/libftprintf.a
LIBFT    = includes/libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJETS) $(FTPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJETS) \
	-L$(FTPRINTF_DIR) -lftprintf \
	-L$(LIBFT_DIR) -lft \
	-lreadline \
	-o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(FTPRINTF):
	@$(MAKE) -C $(FTPRINTF_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(FTPRINTF_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJETS)

good: all clean

fclean: clean
	@$(MAKE) fclean -C $(FTPRINTF_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

