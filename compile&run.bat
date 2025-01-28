IF EXIST build (
    rmdir /s /q build
)

mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make

..\bin\BoardGames.exe
pause