@echo off
7za a GameData.zip GameData
mkdir build

mkdir SFML\build
cd SFML\build
cmake -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS=OFF -DSFML_USE_STATIC_STD_LIBS=ON -DSFML_USE_SYSTEM_DEPS=OFF ..
cmake --build .
cd .. && cd ..

mkdir zipper\build
cd zipper\build
cmake -DCMAKE_BUILD_TYPE="Release" ..
cmake --build .
cd .. && cd ..
