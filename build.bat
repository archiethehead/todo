@echo off
cl Source\*.c External\getopt\*.c /I "./External" /I "./Include" /Fe:"Build/todo.exe"
del *.obj
