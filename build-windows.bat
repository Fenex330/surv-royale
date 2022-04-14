IF %1==workflow (
    set CC=.\mingw64\bin\g++
) ELSE (
    set CC=g++
)

if not exist "build" mkdir "build"
del /s /q build\*

FOR /F %%i IN ('git describe --tags') DO set VAR=%%i

%CC% -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread -DGAME_VERSION=\"%VAR%\" src\client\*.cpp src\client\imgui\*.cpp -o build\surv-royale-client -I win\include -L win\lib -mwindows -lsfml-graphics-2 -lsfml-window-2 -lsfml-audio-2 -lsfml-network-2 -lsfml-system-2 -lopengl32
%CC% -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread -DGAME_VERSION=\"%VAR%\" src\server\*.cpp -o build\surv-royale-server -I win\include -L win\lib -lsfml-network-2 -lsfml-system-2

7z a build\GameData.tar GameData

copy server.conf build
copy LICENSE.txt build
copy CHANGELOG.txt build
copy win\lib\*.dll build
