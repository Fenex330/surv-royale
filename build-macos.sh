mkdir -p build
rm -rf build
mkdir build

clang++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o build/surv-royale-client -F macos/frameworks -rpath @executable_path/ -framework sfml-graphics -framework sfml-window -framework sfml-audio -framework sfml-network -framework sfml-system
clang++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o build/surv-royale-server -F macos/frameworks -rpath @executable_path/ -framework sfml-network -framework sfml-system

tar -cf build/GameData.tar GameData

cp server.conf build
cp LICENSE.txt build
cp CHANGELOG.txt build
