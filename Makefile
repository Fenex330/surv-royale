CXX = g++
CXXFLAGS = -std=c++17 -pedantic-errors -O3 -pthread # -Wall -Wextra
LINKFLAGS_CLIENT = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
LINKFLAGS_SERVER = -lsfml-network -lsfml-system
PREFIX = /usr/local
SHARE_PATH = $(PREFIX)/share/SurvRoyale
BIN_PATH = $(PREFIX)/bin

all: client server

client:
	$(CXX) $(CXXFLAGS) $(LINKFLAGS_CLIENT) src/client/*.cpp -o surv-royale-client

server:
	$(CXX) $(CXXFLAGS) $(LINKFLAGS_SERVER) src/server/*.cpp -o surv-royale-server

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
