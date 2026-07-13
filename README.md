# Team_Strike

A turn-based tactics game written in C. Your team of four faces an AI team of
four on a 10x10 battlefield. Protect the palace at the center — if the AI
destroys it, you lose. Wipe out the AI team to win.

## Units and abilities

- **Your team (1–4)**: each character is either a **Berserker** (deals double
  damage when its own HP drops below 8) or a **Bulldozer** (can smash through
  `O` obstacle tiles).
- **AI team**: `D` guards (tanky, low attack) and `X` strikers (fragile, high
  attack). The AI hunts your closest unit and pushes toward the palace.
- **Map**: `P` palace, `8` palace defenders, `O` obstacles, `.` open ground.

Move into an enemy's tile to attack it. Every move you make (even a blocked
one) ends your turn and the AI moves next.

## Building

Requires gcc. On Windows, MSYS2/MinGW gcc works:

```
make            # builds run_game (terminal game) and engine (for the web UI)
```

Or compile directly:

```
gcc -Wall -I ./header src/run_game.c src/generate_team.c src/load_function.c \
    src/save_function.c src/map_function.c src/move_function.c src/bot_logic.c \
    src/palace.c -o run_game -lm
```

## Playing in the terminal

```
./run_game
```

- `p` to play, `s` to save, `q` to quit
- Select a character `1`–`4`, then `w`/`a`/`s`/`d` to move or `x` to skip
- Saves can be loaded at startup by answering `y` and giving the file name

## Playing in the browser (web front end)

Requires Node.js (no npm packages needed).

```
make web        # or: node web/server.js
```

Then open http://localhost:3117. Click a unit (or press `1`–`4`) to select it,
move with WASD/arrow keys or the on-screen d-pad, `x` to skip a turn. The web
UI runs the same C game logic through `engine` (built from `src/engine.c`),
which speaks a small line/JSON protocol over stdin/stdout.
