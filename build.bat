@echo off
cl Source\*.c /I "./External" /I "./Include" /Fe:"Build/Plan.exe"
del *.obj
