NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f 

SRC = main.c  \
	init_data.c \
	utils.c 

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
	