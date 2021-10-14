if not exist "build" mkdir "build"
del /s /q build\*

g++ -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread src\client\*.cpp -o build\surv-royale-client -I win\include -L win\lib -mwindows -lsfml-graphics-2 -lsfml-window-2 -lsfml-audio-2 -lsfml-network-2 -lsfml-system-2
g++ -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread src\server\*.cpp -o build\surv-royale-server -I win\include -L win\lib -lsfml-network-2 -lsfml-system-2

7z a build\GameData.tar GameData

copy server.conf build
copy LICENSE.txt build
copy CHANGELOG.txt build
copy win\lib\*.dll build
