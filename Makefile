CXX = g++
CXXFLAGS = -std=c++17 -pedantic-errors
APPIMAGE_FLAGS = -DAPPIMAGE
GAME_VERSION := -DGAME_VERSION='"$(shell git describe)"'
DEBUG_FLAGS = -O0 -g -Wall -Wextra -Wno-reorder -ftrapv
RELEASE_FLAGS = -O3 -DNDEBUG
RELEASE_MAX_FLAGS = -Ofast -march=native -DNDEBUG
LIBS_CLIENT = -pthread -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lGL
LIBS_SERVER = -pthread -lsfml-network -lsfml-system
PREFIX ?= /usr/local
SHARE_PATH = $(PREFIX)/share/SurvRoyale
BIN_PATH = $(PREFIX)/bin

# additional warning flags: -Werror, -Weffc++, -Weverything (clang only)
# export LD_LIBRARY_PATH=<sfml-install-path>/lib && ./sfml-app

.PHONY: all appimage debug release release-max client server client-serial server-serial clean install uninstall package
all: release client-serial server-serial

appimage:
	$(eval CXXFLAGS += $(APPIMAGE_FLAGS))

debug:
	$(eval CXXFLAGS += $(DEBUG_FLAGS))

release:
	$(eval CXXFLAGS += $(RELEASE_FLAGS))

release-max:
	$(eval CXXFLAGS += $(RELEASE_MAX_FLAGS))

client:
	parallel $(CXX) $(CXXFLAGS) $(GAME_VERSION) -pipe -c {} -o {}.o ::: src/client/*.cpp src/client/imgui/*.cpp
	$(CXX) src/client/*.o src/client/imgui/*.o $(LIBS_CLIENT) -o surv-royale-client

server:
	parallel $(CXX) $(CXXFLAGS) $(GAME_VERSION) -pipe -c {} -o {}.o ::: src/server/*.cpp
	$(CXX) src/server/*.o $(LIBS_SERVER) -o surv-royale-server

client-serial:
	$(CXX) $(CXXFLAGS) $(GAME_VERSION) $(LIBS_CLIENT) src/client/*.cpp src/client/imgui/*.cpp -o surv-royale-client

server-serial:
	$(CXX) $(CXXFLAGS) $(GAME_VERSION) $(LIBS_SERVER) src/server/*.cpp -o surv-royale-server

clean:
	rm surv-royale-client &
	rm surv-royale-server &
	rm src/client/*.o &
	rm src/client/imgui/*.o &
	rm src/server/*.o &
	rm imgui.ini &
	rm ID &
	rm *.AppImage &
	rm -rf build &

install:
	mkdir $(SHARE_PATH)
	cp server.conf $(SHARE_PATH)
	cp LICENSE.txt $(SHARE_PATH)
	cp CHANGELOG.txt $(SHARE_PATH)
	cp surv-royale-client $(BIN_PATH)
	cp surv-royale-server $(BIN_PATH)
	tar -cf $(SHARE_PATH)/GameData.tar GameData

uninstall:
	rm -rf $(SHARE_PATH) &
	rm $(BIN_PATH)/surv-royale-client &
	rm $(BIN_PATH)/surv-royale-server &

package:
	mkdir -p build
	rm -rf build
	mkdir -p build/AppDir/usr/bin
	mkdir -p build/AppDir/usr/lib
	mkdir -p build/AppDir/usr/share
	$(MAKE) install PREFIX=build/AppDir/usr
	cp /usr/lib/libsfml-* build/AppDir/usr/lib
	cp appimage/SurvRoyale.sh build/AppDir/usr/bin/SurvRoyale
	cp appimage/SurvRoyale.desktop build/AppDir
	cp appimage/SurvRoyale.png build/AppDir
	cp appimage/AppRun build/AppDir
	appimage/linuxdeploy-x86_64.AppImage --appdir build/AppDir --output appimage
