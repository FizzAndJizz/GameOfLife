@echo off
mkdir ..\build
pushd ..\build
cl /std:clatest ..\src\GameOfLife.c gdi32.lib kernel32.lib msvcrt.lib opengl32.lib raylib.lib shell32.lib user32.lib winmm.lib  -Ic:\raylib\raylib\out\build\x64-Debug\raylib\include /link /libpath:c:\raylib\raylib\out\build\x64-Debug\raylib\ 
popd

