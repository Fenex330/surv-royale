mkdir -p build
rm -rf build
mkdir build

c++ -std=c++17 -pedantic-errors -O3 -Izipper -Lzipper -pthread src/client/*.cpp -o build/surv-royale-client \
-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lZipper-static -lz # -Wall -Wextra

c++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -lsfml-network -lsfml-system

7za a build/GameData.zip GameData

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
