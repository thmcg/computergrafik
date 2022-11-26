UNAME = $(shell uname -s)
ifeq ($(findstring NT,$(UNAME)),NT)
	INC = -I../libraries/glfw-3.3.4.bin.WIN64/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.4.bin.WIN64/lib-mingw-w64
	LNK = -l glfw3 -l gdi32 -l opengl32
	OPT = 
else ifeq ($(findstring Darwin,$(UNAME)),Darwin)
	INC = -I../libraries/glfw-3.3.4.bin.MACOS/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.4.bin.MACOS/lib-universal
	LNK = -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit
	OPT = -arch arm64 -arch x86_64 -std=c++20 -Wno-deprecated
else ifeq ($(findstring Linux,$(UNAME)),Linux)
	INC = -I../libraries/glad/include
	LIB = 
	LNK = -lglfw -lrt -lm -ldl -lGL
	OPT =
endif

bin/engine: obj/main.o obj/graphics.o obj/window.o obj/game.o obj/shader.o obj/mesh.o obj/texture.o obj/filereader.o obj/model.o | bin
	g++ -g obj/*.o -o bin/engine $(LIB) $(LNK) $(OPT)

obj/main.o: main.cpp | obj
	g++ -g -c main.cpp -o obj/main.o $(INC) $(OPT)

obj/graphics.o: graphics.cpp | obj
	g++ -g -c graphics.cpp -o obj/graphics.o $(INC) $(OPT)

obj/window.o: window.cpp | obj
	g++ -g -c window.cpp -o obj/window.o $(INC) $(OPT)

obj/game.o: game.cpp | obj
	g++ -g -c game.cpp -o obj/game.o $(INC) $(OPT)

obj/shader.o: shader.cpp | obj
	g++ -g -c shader.cpp -o obj/shader.o $(INC) $(OPT)

obj/mesh.o: mesh.cpp | obj
	g++ -g -c mesh.cpp -o obj/mesh.o $(INC) $(OPT)

obj/texture.o: texture.cpp | obj
	g++ -g -c texture.cpp -o obj/texture.o $(INC) $(OPT)

obj/filereader.o: filereader.cpp | obj
	g++ -g -c filereader.cpp -o obj/filereader.o $(INC) $(OPT)

obj/model.o: model.cpp | obj
	g++ -g -c model.cpp -o obj/model.o $(INC) $(OPT)

bin:
	mkdir -p bin

obj:
	mkdir -p obj

run: bin/engine
	bin/engine

clean:
	rm -rf obj
	rm -rf bin
