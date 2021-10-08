mkdir -p build
rm -rf build
mkdir build

clang++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -lsfml-network-s -lsfml-system-s

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
