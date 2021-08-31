CC = gcc
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
LDFLAGS = $(SDL_LDFLAGS) -lm -ldl
CFLAGS = -Wall -Wextra -Werror $(SDL_CFLAGS)

SUBJECTS = main.c window.c putpixel.c point3d.c sphere.c ee_print_color.c
OBJECTS = $(SUBJECTS:.c=.o)
NAME = raytracing


all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(OBJECTS)

fclean:
	rm -rf $(NAME)
