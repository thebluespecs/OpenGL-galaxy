run : Controller.o main.o Model.o Parser.o Renderer.o Shader.o Vertex.o View.o Texture.o stb_image.o
	g++ -std=c++11 -o bin/exe Controller.o main.o Model.o Parser.o Renderer.o Shader.o Vertex.o View.o Texture.o stb_image.o -w -lGL -lglfw -lGLEW -lGLU
	./bin/exe

Controller.o : src/Controller.cpp src/View.h src/Renderer.h src/Texture.h
	g++ -std=c++11 -c src/Controller.cpp

main.o : src/main.cpp src/Controller.h
	g++ -std=c++11 -c src/main.cpp

Model.o : src/Model.cpp src/Shader.h src/Parser.h
	g++ -std=c++11 -c src/Model.cpp

Parser.o : src/Parser.cpp src/Vertex.h
	g++ -std=c++11 -c src/Parser.cpp

Renderer.o : src/Renderer.cpp src/Model.h
	g++ -std=c++11 -c src/Renderer.cpp

Shader.o : src/Shader.cpp
	g++ -std=c++11 -c src/Shader.cpp

Vertex.o : src/Vertex.cpp
	g++ -std=c++11 -c src/Vertex.cpp

View.o : src/View.cpp 
	g++ -std=c++11 -c src/View.cpp

Texture.o : src/Texture.cpp
	g++ -std=c++11 -c src/Texture.cpp

stb_image.o : src/stb_image.cpp
	g++ -std=c++11 -c src/stb_image.cpp

dump :
	rm *.o bin/exe