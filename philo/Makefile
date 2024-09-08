NAME		= philo
SRCS		= main.c utils.c thread.c routine.c destroy.c monitor.c \
init.c action.c
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -pthread -g -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror -pthread -g -fsanitize=thread
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -I includes

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re