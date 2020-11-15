  all:
	g++ -c ./SeaOneScene.cpp -lglut -lGL -lGLU
	g++ -c ./SeaComponents.cpp -lglut -lGL -lGLU
	g++ -c ./SeaDraw.cpp -lglut -lGL -lGLU
	g++ -c ./SeaNetworkTABLE.cpp -pthread
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaNetworkTABLE.o SeaDraw.o -lglut -lGL -lGLU -pthread
	./a.out