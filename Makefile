CXX = g++
CXXFLAGS = -std=c++17 -pedantic-errors
DEBUG_FLAGS = -O0 -g -Wall -Wextra -ftrapv
RELEASE_FLAGS = -O3 -DNDEBUG
RELEASE_MAX_FLAGS = -Ofast -march=native -DNDEBUG
LIBS_CLIENT = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
LIBS_SERVER = -lsfml-network -lsfml-system
PREFIX = /usr/local
SHARE_PATH = $(PREFIX)/share/SurvRoyale
BIN_PATH = $(PREFIX)/bin

# additional compiler flags: -Weffc++, -Weverything (clang only), -pthread

all: release client-serial server-serial

debug:
	$(eval CXXFLAGS += $(DEBUG_FLAGS))

release:
	$(eval CXXFLAGS += $(RELEASE_FLAGS))

release-max:
	$(eval CXXFLAGS += $(RELEASE_MAX_FLAGS))

client:
	parallel $(CXX) $(CXXFLAGS) -pipe -c {} -o {.}.o ::: src/client/*.cpp
	$(CXX) src/client/*.o $(LIBS_CLIENT) -o surv-royale-client

server:
	parallel $(CXX) $(CXXFLAGS) -pipe -c {} -o {.}.o ::: src/server/*.cpp
	$(CXX) src/server/*.o $(LIBS_SERVER) -o surv-royale-server

client-serial:
	$(CXX) $(CXXFLAGS) $(LIBS_CLIENT) src/client/*.cpp -o surv-royale-client

server-serial:
	$(CXX) $(CXXFLAGS) $(LIBS_SERVER) src/server/*.cpp -o surv-royale-server

clean:
	rm surv-royale-client &
	rm surv-royale-server &
	rm src/client/*.o &
	rm src/server/*.o &

install:
	mkdir $(SHARE_PATH)
	tar -cf $(SHARE_PATH)/GameData.tar GameData &
	cp server.conf $(SHARE_PATH) &
	cp LICENSE.txt $(SHARE_PATH) &
	cp CHANGELOG.txt $(SHARE_PATH) &
	cp surv-royale-client $(BIN_PATH) &
	cp surv-royale-server $(BIN_PATH) &

uninstall:
	rm -rf $(SHARE_PATH) &
	rm $(BIN_PATH)/surv-royale-client &
	rm $(BIN_PATH)/surv-royale-server &
