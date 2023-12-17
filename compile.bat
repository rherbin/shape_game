REM gcc -Wall ansi_escape.c main.c -o main
gcc ansi_escape.c main.c -I.\SDL2\include -L.\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main