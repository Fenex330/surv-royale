if not exist "build" mkdir "build"
del /s /q build\*

c++ -std=c++17 -pedantic-errors -O3 -pthread src\client\*.cpp -o build\surv-royale-client -Izipper -Iwin\include -Lwin\lib -lsfml-graphics-2 -lsfml-window-2 -lsfml-audio-2 -lsfml-network-2 -lsfml-system-2 -lZipper -lz
c++ -std=c++17 -pedantic-errors -O3 -pthread src\server\*.cpp -o build\surv-royale-server -Iwin\include -Lwin\lib -lsfml-network-2 -lsfml-system-2

7z a build\GameData.zip GameData

copy server.conf build
copy LICENSE.txt build
copy CHANGELOG.txt build
copy win\lib\*.dll build
