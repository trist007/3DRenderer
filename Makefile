CC = C:/msys64/ucrt64/bin/gcc.exe
CFLAGS = -IC:/sdl2/SDL2-2.30.11/include -IC:/msys64/ucrt64/include -Wall -std=c99 -Wno-unused-variable

LIBS = -LC:/sdl2/SDL2-2.30.11/lib/x64 -lSDL2main -lSDL2 -lm

build:
	$(CC) ./src/*.c $(CFLAGS) $(LIBS) -o renderer.exe

run:
	./renderer.exe

clean:
	rm renderer.exe
