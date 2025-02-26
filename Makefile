all:
	g++ -Iinclude -Llib main.cpp include/Platformer-V2.0/object.cpp include/Platformer-V2.0/dynamicobject.cpp include/Platformer-V2.0/physics.cpp -o main -lmingw32 -lSDL2main -lSDL2 -static-libstdc++
	./main