@echo off
nasm -f win32 source\strequal.asm -o Build\strequal.obj
cl /c Source\*.c /I "./External" /I "./Include" /Fo:"Build/Plan.obj"
link Build\Plan.obj Build\strequal.obj /OUT:Build\Plan.exe
del Build\*.obj
