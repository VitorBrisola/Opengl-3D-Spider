all:
	@g++ -o T2 src/T2.cpp src/Geometrics.cpp src/Spider.cpp src/Transformations.cpp src/ilumination.cpp src/texture.cpp -I include/ -g -Wall -lglut -lGLU -lGL -lm -lopencv_core -lopencv_imgproc -lopencv_highgui -std=c++11	
run:
	@./T2
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./T2