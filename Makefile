all:
	g++ -I SDL/include/SDL2 -L SDL/lib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && main.exe