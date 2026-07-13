@echo off
cl Source\*.c /I "./External" /I "./Include" /Fe:Plan.exe
del *.obj
