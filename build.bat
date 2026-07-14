@echo off
cl Source\*.c External\sqlite3\*.c /I "./External" /I "./Include" /Fe:"Build/Plan.exe"
del *.obj
