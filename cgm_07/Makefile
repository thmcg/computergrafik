UNAME = $(shell uname -s)
ifeq ($(findstring NT,$(UNAME)),NT)
	INC = -I../libraries/glfw-3.3.8.bin.WIN64/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.8.bin.WIN64/lib-mingw-w64
	LNK = -l glfw3 -l gdi32 -l opengl32
	OPT = 
else ifeq ($(findstring Darwin,$(UNAME)),Darwin)
	INC = -I../libraries/glfw-3.3.8.bin.MACOS/include -I../libraries/glad/include
	LIB = -L../libraries/glfw-3.3.8.bin.MACOS/lib-universal
	LNK = -l glfw3 -framework Cocoa -framework OpenGL -framework IOKit
	OPT = -arch arm64 -arch x86_64 -std=c++20 -Wno-deprecated
else ifeq ($(findstring Linux,$(UNAME)),Linux)
	INC = -I../libraries/glad/include
	LIB = 
	LNK = -lglfw -lrt -lm -ldl -lGL
	OPT = -std=c++20
endif

bin/engine: obj/main.o obj/graphics.o obj/window.o obj/game.o obj/shader.o obj/mesh.o obj/texture.o obj/filereader.o obj/model.o | bin
	g++ -g obj/*.o -o $@ $(LIB) $(LNK) $(OPT)

obj/main.o: main.cpp settings.h | obj
	g++ -g -c main.cpp -o $@ $(INC) $(OPT)

obj/graphics.o: graphics.cpp cgmath.h settings.h vertex.h model.h mesh.h shader.h texture.h | obj
	g++ -g -c graphics.cpp -o $@ $(INC) $(OPT)

obj/window.o: window.cpp settings.h | obj
	g++ -g -c window.cpp -o $@ $(INC) $(OPT)

obj/game.o: game.cpp settings.h cgmath.h | obj
	g++ -g -c game.cpp -o $@ $(INC) $(OPT)

obj/shader.o: shader.cpp shader.h cgmath.h texture.h | obj
	g++ -g -c shader.cpp -o $@ $(INC) $(OPT)

obj/mesh.o: mesh.cpp mesh.h vertex.h cgmath.h filereader.h | obj
	g++ -g -c mesh.cpp -o $@ $(INC) $(OPT)

obj/texture.o: texture.cpp texture.h stb_image.h | obj
	g++ -g -c texture.cpp -o $@ $(INC) $(OPT)

obj/filereader.o: filereader.cpp filereader.h cgmath.h | obj
	g++ -g -c filereader.cpp -o $@ $(INC) $(OPT)

obj/model.o: model.cpp model.h cgmath.h mesh.h vertex.h shader.h texture.h filereader.h | obj
	g++ -g -c model.cpp -o $@ $(INC) $(OPT)

bin:
	mkdir -p bin

obj:
	mkdir -p obj

run: bin/engine
	bin/engine

clean:
	rm -rf obj
	rm -rf bin
