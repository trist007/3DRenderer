export MSYS2_ARG_CONV_EXCL=*

# Adjust to your MSVC-compatible SDL2 dev package
SDL2_INC = C:/sdl2/SDL2-2.30.11/include
SDL2_LIB = C:/sdl2/SDL2-2.30.11/lib/x64

#CFLAGS  = /nologo /I$(SDL2_INC)  /Zi /std:c11
# /wd4101 suppresses "unused local variable" (closest MSVC equivalent to -Wno-unused-variable)

LDFLAGS = /link /LIBPATH:$(SDL2_LIB) /SUBSYSTEM:CONSOLE

build:
	$(CC) $(CFLAGS) src/*.c /Fe:renderer.exe /Fd:renderer.pdb $(INCLUDES) $(LIBS) $(LDFLAGS)

run:
	./renderer.exe

checkenv:
	@echo INCLUDES=$$INCLUDES

clean:
	rm -f renderer.exe renderer.pdb *.obj
