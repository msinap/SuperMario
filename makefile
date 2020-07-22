CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer


all: a.out

a.out: main.o rsdl.o utility.o Game.o Camera.o Player.o Keyboard.o Background.o Speaker.o Map.o Mario.o Block.o Brick.o Enemy.o Mushroom.o Coin.o
	$(CC) make/main.o make/utility.o make/Game.o make/Camera.o make/Player.o make/Keyboard.o make/Speaker.o make/Background.o make/Map.o make/Mario.o make/Block.o make/Brick.o make/Enemy.o make/Mushroom.o make/Coin.o make/rsdl.o $(CCFLAGS)

main.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/main.cpp
	$(CC) -c code/main.cpp -o make/main.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
	$(CC) -c src/rsdl.cpp -o make/rsdl.o

utility.o: src/rsdl.hpp code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o

Game.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Game.cpp
	$(CC) -c code/Game.cpp -o make/Game.o

Camera.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Camera.cpp
	$(CC) -c code/Camera.cpp -o make/Camera.o

Player.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Camera.cpp
	$(CC) -c code/Player.cpp -o make/Player.o

Keyboard.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Keyboard.cpp
	$(CC) -c code/Keyboard.cpp -o make/Keyboard.o

Speaker.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Speaker.cpp
	$(CC) -c code/Speaker.cpp -o make/Speaker.o

Background.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Background.cpp
	$(CC) -c code/Background.cpp -o make/Background.o

Map.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Map.cpp
	$(CC) -c code/Map.cpp -o make/Map.o

Mario.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Mario.cpp
	$(CC) -c code/Mario.cpp -o make/Mario.o

Block.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Block.cpp
	$(CC) -c code/Block.cpp -o make/Block.o

Brick.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Brick.cpp
	$(CC) -c code/Brick.cpp -o make/Brick.o

Enemy.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Enemy.cpp
	$(CC) -c code/Enemy.cpp -o make/Enemy.o

Mushroom.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Mushroom.cpp
	$(CC) -c code/Mushroom.cpp -o make/Mushroom.o

Coin.o: src/rsdl.hpp code/utility.h code/Camera.h code/Player.h code/Keyboard.h code/Speaker.h code/Background.h code/Map.h code/Mario.h code/Block.h code/Brick.h code/Enemy.h code/Mushroom.h code/Coin.h code/Game.h code/Coin.cpp
	$(CC) -c code/Coin.cpp -o make/Coin.o

.PHONY: clean
clean:
	rm -r make/*.o
