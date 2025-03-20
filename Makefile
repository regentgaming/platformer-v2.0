all:
	g++ -Iinclude -Llib main.cpp include/Platformer-V2.0/object.cpp include/Platformer-V2.0/dynamic_object.cpp include/Platformer-V2.0/physics.cpp include/Platformer-V2.0/default_player.cpp include/Platformer-V2.0/default_player_controller.cpp -o main -lmingw32 -lSDL3 -static-libstdc++
	./main
