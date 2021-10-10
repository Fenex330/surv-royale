client:
	g++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o surv-royale-client -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system # -Wall -Wextra

server:
	g++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o surv-royale-server -lsfml-network -lsfml-system

clean:
	mkdir -p /usr/local/share/SurvRoyale
	rm -rf /usr/local/share/SurvRoyale
	mkdir /usr/local/share/SurvRoyale

prepare:
	tar -cf /usr/local/share/SurvRoyale/GameData.tar GameData
	cp server.conf /usr/local/share/SurvRoyale/
	cp LICENSE.txt /usr/local/share/SurvRoyale/
	cp CHANGELOG.txt /usr/local/share/SurvRoyale/

install:
	make clean prepare

all:
	make client server
