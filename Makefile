# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = 42ping

SRCS = srcs/main.c \
	srcs/help.c \
	srcs/core/core.c \
	srcs/core/tools.c \
	srcs/core/error.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)