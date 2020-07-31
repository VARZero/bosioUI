  all:
	g++ -c ./SeaOneScene.cpp -lglut -lGL -lGLU
	g++ -c ./SeaComponents.cpp -lglut -lGL -lGLU
	g++ -c ./SeaDraw.cpp -lglut -lGL -lGLU
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaDraw.o -lglut -lGL -lGLU
	./a.out