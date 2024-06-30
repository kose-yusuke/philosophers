NAME		= philo
SRCS		= main.c
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
OBJS		= $(SRCS:.c=.o)
OBJS_DIR	= objs
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