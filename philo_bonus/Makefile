NAME = philo_bonus

CC = CC

CFLAGS = -Wall -Wextra -Werror

RM = rm -f 

SRC = main.c \
	parse_data.c \
	routine.c \
	kill_processes.c \
	utils.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo $@ created

%.o : %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling '$<'... Done."

clean : 
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
	