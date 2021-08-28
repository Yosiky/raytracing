CC = gcc
FLAGS = -Wall -Wextra -Werror

SUBJECTS = main.c
OBJECTS = $(SUBJECTS:.c=.o)
NAME = raytracing

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(FLAGS) $< -c -o $@
