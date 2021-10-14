CXX = g++
CXXFLAGS = -std=c++17 -pedantic-errors # -pthread -Wall -Wextra
RELEASE_FLAGS = -O3 -DNDEBUG
DEBUG_FLAGS = -O0 -g
LIBS_CLIENT = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
LIBS_SERVER = -lsfml-network -lsfml-system
PREFIX = /usr/local
SHARE_PATH = $(PREFIX)/share/SurvRoyale
BIN_PATH = $(PREFIX)/bin

all: release client server

release: CXXFLAGS += $(RELEASE_FLAGS)

debug: CXXFLAGS += $(DEBUG_FLAGS)

client:
	$(CXX) $(CXXFLAGS) $(LIBS_CLIENT) src/client/*.cpp -o surv-royale-client

server:
	$(CXX) $(CXXFLAGS) $(LIBS_SERVER) src/server/*.cpp -o surv-royale-server

clean:
	rm surv-royale-client
	rm surv-royale-server

install:
	mkdir $(SHARE_PATH)
	tar -cf $(SHARE_PATH)/GameData.tar GameData
	cp server.conf $(SHARE_PATH)
	cp LICENSE.txt $(SHARE_PATH)
	cp CHANGELOG.txt $(SHARE_PATH)
	cp surv-royale-client $(BIN_PATH)
	cp surv-royale-server $(BIN_PATH)

uninstall:
	rm -rf $(SHARE_PATH)
	rm $(BIN_PATH)/surv-royale-client
	rm $(BIN_PATH)/surv-royale-server
