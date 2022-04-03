#export LD_LIBRARY_PATH=<sfml-install-path>/lib && ./sfml-app
#cp /usr/lib/libsfml-* .
#wget https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip

mkdir -p build
rm -rf build
mkdir build
cd build
mkdir AppDir
unzip ../appimage/SFML-*-sources.zip
cd SFML-*
mkdir build
cd build
cmake .. -G"Ninja" -DCMAKE_INSTALL_PREFIX="/usr" -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS=ON -DSFML_BUILD_AUDIO=ON -DSFML_BUILD_GRAPHICS=ON -DSFML_BUILD_WINDOW=ON -DSFML_BUILD_NETWORK=ON -DSFML_BUILD_DOC=OFF -DSFML_BUILD_EXAMPLES=OFF
ninja all
ninja install DESTDIR=../../AppDir
cd ../../..
mkdir build/AppDir/usr/bin
make install PREFIX=build/AppDir/usr
appimage/linuxdeploy-x86_64.AppImage --appdir build/AppDir --output appimage
