CC = gcc
CFLAGS = -Wall -I ./header
DEPS = header/generate_character.h header/team.h header/tile.h header/character.h header/save_function.h header/load_function.h header/move_function.h header/map_function.h

TARGET = run_game 

SRCS = src/run_game.c src/generate_team.c src/load_function.c src/save_function.c src/map_function.c src/move_function.c 
OBJS = $(SRCS:src/%.c=src/%.o)    

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

test:
	./$(TARGET)           

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
