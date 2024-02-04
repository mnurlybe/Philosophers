NAME = philo

SOURCES = 	main.c \
			errors.c \
			init_structs.c \
			print.c \
			free.c \
			utils.c \
			head_routine.c \
			stop_philo.c \
			write_messages.c \
			philo_utils.c \
  
OBJ_DIR = obj
MY_HEADER = ./includes/

CFLAGS = -Wall -Wextra -Werror
LIBS = -lpthread
FSANITIZE = -g3 -fsanitize=address

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean	
	rm -f $(NAME)

re: fclean all