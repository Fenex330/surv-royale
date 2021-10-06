mkdir -p build
rm -rf build
mkdir build

cp -R SFML.framework build

clang++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o build/surv-royale-client -I build/SFML.framework/Headers -F build -rpath @executable_path -framework SFML
clang++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -I build/SFML.framework/Headers -F build -rpath @executable_path -framework SFML

tar -cf build/GameData.tar GameData

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
