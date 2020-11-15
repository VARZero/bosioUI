all:
	g++ -c ./SeaOneScene.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./SeaComponents.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./SeaDraw.cpp -std=c++11 -lglut -lGL -lGLU
	g++ -c ./SeaNetworkTABLE.cpp -std=c++11 -pthread
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaNetworkTABLE.o SeaDraw.o -lglut -lGL -lGLU -pthread
	./a.out

mac:
	g++ -c ./SeaOneScene.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./SeaComponents.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./SeaDraw.cpp -std=c++11 -framework OPENGL -framework GLUT
	g++ -c ./SeaNetworkTABLE.cpp -std=c++11 -pthread
	g++ -o a.out SeaComponents.o SeaOneScene.o SeaNetworkTABLE.o SeaDraw.o -framework OPENGL -framework GLUT -pthread
	./a.out