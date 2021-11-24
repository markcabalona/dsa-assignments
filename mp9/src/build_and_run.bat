@echo off
cls
echo Compiling...
g++ main.cpp models/*.cpp providers/*.cpp screens/*.cpp utils/*.cpp db/*.cpp -o app.exe
echo PRESS CTRL + C to EXIT
timeout 3
:wait
if exist app.exe (echo App is booting. Please Wait && app) else (timeout 3 && goto wait)
del app.exe