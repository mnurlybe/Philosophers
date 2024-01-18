NAME = philo

SOURCES = 	main.c \
			utils.c \
			init_structs.c \
			routine.c \
			write_messages.c \
			errors.c \
			free.c \
			# print.c \
  
OBJ_DIR = obj
MY_HEADER = ./includes/

CFLAGS = -Wall -Wextra -Werror
LIBS = -lpthread
# FSANITIZE = -g3 -fsanitize=address

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