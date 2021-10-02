mkdir -p build
rm -rf build
mkdir build

g++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o build/surv-royale-client -Izipper -Lzipper -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lZipper-static -lz # -Wall -Wextra
g++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -lsfml-network -lsfml-system

7z a build/GameData.zip GameData

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
