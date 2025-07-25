# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = 42ping

SRCS = srcs/main.c \
	srcs/help.c \
	srcs/core/core.c \
	srcs/core/init.c \
	srcs/core/print.c \
	srcs/core/args.c \
	srcs/core/tools.c \
	srcs/core/error.c \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/

LDFLAGS = -lm

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS)

right:
	@sudo setcap cap_net_raw+ep $(NAME)

re: fclean all right

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
