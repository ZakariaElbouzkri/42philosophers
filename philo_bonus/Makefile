NAME = philo_bonus

CC = CC -std=c11
CC += -Wall -Wextra -Werror
CC += -g -fsanitize=thread
CC += -pthread

RM = rm -f 

SRC = main.c parse_data.c utils.c

OBJ = $(SRC:.c=.o)

all :: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $^ -o $@
	@echo $@ created

%.o : %.c philo.h
	@$(CC) -c $< -o $@
	@echo "Compiling '$<'... Done."

clean : 
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re : fclean all
	