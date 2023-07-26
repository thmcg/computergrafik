bin/engine: obj/main.o | bin
	g++ -g obj/*.o -o bin/engine

obj/main.o: main.cpp | obj
	g++ -g -c main.cpp -o obj/main.o

bin:
	mkdir -p bin

obj:
	mkdir -p obj

run: bin/engine
	bin/engine

clean:
	rm -rf obj
	rm -rf bin
