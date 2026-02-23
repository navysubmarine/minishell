NAME = pipex
CC = cc 
AR = ar rcs
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -I. -I $(LIBFT_DIR)

SRCS = $(C_FILES)

INC = -I includes
C_FILES = pipex.c \
	utilis.c \
	ft_error.c \

OBJS = $(SRCS:.c=.o)
all: $(NAME) $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(LIBFT_DIR) -lft

$(LIBFT):
	make -C $(LIBFT_DIR)

clean: 
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re