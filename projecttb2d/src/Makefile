CC=g++
SRC = Actor.cpp Bullet.cpp Core.cpp Crafter.cpp Entity.cpp global.cpp HQ.cpp ImageManager.cpp Item.cpp Menu.cpp NPC.cpp Player.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Weapon.cpp World.cpp

OBJ = $(SRC:.cpp=.o)

LIB = -lsfml-graphics -lsfml-system -lsfml-window


all:	$(OBJ)
	$(CC) -g  $(OBJ) $(LIB) ../main.cpp -o ../exe

Actor.o:	Actor.cpp Actor.h
		$(CC) -c Actor.cpp -o Actor.o

Bullet.o:	Bullet.cpp Bullet.h
		$(CC) -c Bullet.cpp -o Bullet.o

Core.o:		Core.cpp Core.h
		$(CC) -c Core.cpp -o Core.o

Crafter.o:	Crafter.cpp Crafter.h
		$(CC) -c Crafter.cpp -o Crafter.o

Entity.o:	Entity.cpp Entity.h
		$(CC) -c Entity.cpp -o Entity.o

global.o:	global.cpp global.h
		$(CC) -c global.cpp -o global.o

HQ.o:		HQ.cpp HQ.h
		$(CC) -c HQ.cpp -o HQ.o


ImageManager.o:	ImageManager.cpp ImageManager.h
		$(CC) -c ImageManager.cpp -o ImageManager.o


Item.o:		Item.cpp Item.h
		$(CC) -c Item.cpp -o Item.o


Menu.o:		Menu.cpp Menu.h
		$(CC) -c Menu.cpp -o Menu.o

NPC.o:		NPC.cpp NPC.h
		$(CC) -c NPC.cpp -o NPC.o

Player.o:	Player.cpp Player.h	
		$(CC) -c Player.cpp -o Player.o

tinystr.o:	tinystr.cpp tinystr.h
		$(CC) -c tinystr.cpp -o tinystr.o

tinyxml.o:	tinyxml.cpp tinyxml.h
		$(CC) -c tinyxml.cpp -o tinyxml.o

tinyxmlerror.o:	tinyxmlerror.cpp tinyxml.h
		$(CC) -c tinyxmlerror.cpp -o tinyxmlerror.o

tinyxmlparser.o:tinyxmlparser.cpp tinyxml.h
		$(CC) -c tinyxmlparser.cpp -o tinyxmlparser.o

Weapon.o:	Weapon.cpp Weapon.h
		$(CC) -c Weapon.cpp -o Weapon.o

World.o:	World.cpp World.h
		$(CC) -c World.cpp -o World.o

clean:	
	rm -v *.o *~


