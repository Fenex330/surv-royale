client:
	g++ -std=c++17 -pedantic-errors -O3 -pthread src/client/*.cpp -o surv-royale-client -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system # -Wall -Wextra

server:
	g++ -std=c++17 -pedantic-errors -O3 -pthread src/server/*.cpp -o surv-royale-server -lsfml-network -lsfml-system

clean:
	rm -rf /usr/local/share/SurvRoyale
	rm surv-royale-client
	rm surv-royale-server
	rm /usr/local/bin/surv-royale-client
	rm /usr/local/bin/surv-royale-server

install:
	mkdir /usr/local/share/SurvRoyale
	tar -cf /usr/local/share/SurvRoyale/GameData.tar GameData
	cp server.conf /usr/local/share/SurvRoyale
	cp LICENSE.txt /usr/local/share/SurvRoyale
	cp CHANGELOG.txt /usr/local/share/SurvRoyale
	cp surv-royale-client /usr/local/bin
	cp surv-royale-server /usr/local/bin

all:
	make client
	make server
