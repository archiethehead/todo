@echo off
rc /fo .\icon.res .\Source\icon.rc
cl Source\*.c External\getopt\*.c .\icon.res /I "./External" /I "./Include" /Fe:"Build/todo.exe"
del *.obj
del *.res
