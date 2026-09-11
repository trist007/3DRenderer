@echo off
cd ..
echo deleting *.obj and *.exe
del /q *.obj >nul 2>&1 && del /q *.exe >nul 2>&1
