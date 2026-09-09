@echo off

echo cwd: %CD%

set SDLINCLUDE=C:/sdl2/SDL2-2.30.11/include
set SDLLIB=C:/sdl2/SDL2-2.30.11/lib/x64

set CC=cl.exe
set CFLAGS=/utf-8 /std:c17 /Zc:__STDC__ /EHsc ^
    /MD -nologo -fp:fast -Gm- -Od -Oi -WX -W4 ^
    -wd4202 -wd4100 -wd4189 -wd4244 -wd4996 -wd4456 -wd4324 -wd4505 -wd4267 -wd5287 ^
    -wd4701 -wd4244 -wd4101 -wd4305 ^
    -FC -Z7
set INCLUDES=/I. /Isrc /I%SDLINCLUDE%
set LIBS=kernel32.lib user32.lib gdi32.lib Shell32.lib SDL2.lib SDL2main.lib

echo Compiling renderer.exe...
    make
