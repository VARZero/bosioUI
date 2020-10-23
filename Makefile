  all:
	g++ -c ./SeaOneScene.cpp -lglut -lGL -lGLU
	g++ -c ./SeaComponents.cpp -lglut -lGL -lGLU
	g++ -c ./SeaDraw.cpp -lglut -lGL -lGLU
	g++ -c ./SeaNetworkTABLE.cpp
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaDraw.o SeaNetworkTABLE.o -lglut -lGL -lGLU
	./a.out