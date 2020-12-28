all:
	g++ -c ./src/SeaOneScene.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./src/SeaComponents.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./src/SeaDraw.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./src/SeaNetworkTABLE.cpp -std=c++11 -pthread
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaNetworkTABLE.o SeaDraw.o -lglut -lGL -lGLU -pthread
	./a.out

mac:
	g++ -c ./src/SeaOneScene.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./src/SeaComponents.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./src/SeaDraw.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./src/SeaNetworkTABLE.cpp -std=c++11 -pthread
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaNetworkTABLE.o SeaDraw.o -framework OPENGL -framework GLUT -pthread
	./a.out