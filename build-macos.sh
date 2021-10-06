mkdir -p build
rm -rf build
mkdir build

clang++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o build/surv-royale-client -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
clang++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -lsfml-network -lsfml-system

tar -cf build/GameData.tar GameData

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
