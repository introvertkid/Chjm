all:
	g++ -I SDL/include -L SDL/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2