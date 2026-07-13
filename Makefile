CC = gcc
CFLAGS = -Wall -I ./header
DEPS = header/generate_team.h header/team.h header/tile.h header/character.h header/save_function.h header/load_function.h header/move_function.h header/map_function.h header/bot_logic.h header/palace.h

TARGET = run_game
ENGINE = engine

GAME_SRCS = src/generate_team.c src/map_function.c src/move_function.c src/bot_logic.c src/palace.c
SRCS = src/run_game.c src/load_function.c src/save_function.c $(GAME_SRCS)
ENGINE_SRCS = src/engine.c $(GAME_SRCS)
OBJS = $(SRCS:src/%.c=src/%.o)
ENGINE_OBJS = $(ENGINE_SRCS:src/%.c=src/%.o)

all: $(TARGET) $(ENGINE)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

$(ENGINE): $(ENGINE_OBJS)
	$(CC) $(CFLAGS) $(ENGINE_OBJS) -o $(ENGINE) -lm

clean:
	rm -f src/*.o $(TARGET) $(ENGINE) $(TARGET).exe $(ENGINE).exe

test:
	./$(TARGET)

web: $(ENGINE)
	node web/server.js

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
