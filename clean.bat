@echo off
cd ..
echo deleting *.obj and *.exe
del /q /s *.obj >nul 2>&1 && del /q /s *.exe >nul 2>&1
