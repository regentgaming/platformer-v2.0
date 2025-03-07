all:
	g++ -Iinclude -Llib main.cpp include/Platformer-V2.0/object.cpp include/Platformer-V2.0/dynamicobject.cpp include/Platformer-V2.0/physics.cpp include/Platformer-V2.0/player.cpp -o main -lmingw32 -lSDL3 -static-libstdc++
	./main
