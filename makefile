CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
NAME = philo

SRCS = src/onetimecall.c src/creation.c src/action.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all