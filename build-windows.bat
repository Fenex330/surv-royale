if not exist "build" mkdir "build"
del /s /q build\*

git describe --abbrev=100 > tmp
set /p version = < tmp
del tmp

g++ -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread -DGAME_VERSION=version src\client\*.cpp src\client\imgui\*.cpp -o build\surv-royale-client -I win\include -L win\lib -mwindows -lsfml-graphics-2 -lsfml-window-2 -lsfml-audio-2 -lsfml-network-2 -lsfml-system-2 -lopengl32
g++ -std=c++17 -pedantic-errors -O3 -DNDEBUG -pthread -DGAME_VERSION=version src\server\*.cpp -o build\surv-royale-server -I win\include -L win\lib -lsfml-network-2 -lsfml-system-2

7z a build\GameData.tar GameData

copy server.conf build
copy banlist.txt build
copy LICENSE.txt build
copy CHANGELOG.txt build
copy win\lib\*.dll build
