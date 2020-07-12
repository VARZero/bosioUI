  all:
	g++ -c ./SeaOneScene.cpp -lglut -lGL -lGLU
	g++ -c ./SeaDraw.cpp -lglut -lGL -lGLU
	g++ -o a.out SeaOneScene.o SeaDraw.o -lglut -lGL -lGLU
	./a.out