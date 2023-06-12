NAME = philo

CC = cc -Wall -Wextra -Werror
CC += -fsanitize=thread
RM = rm -f

SRCS = main.c init_data.c utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o : %.c philo.h
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:fclean all

.PHONY:all clean fclean re