.PHONY: all run clean

all: test

test: test.cpp
	clang++ test.cpp -o test -I../include -L../dist/osx -lSDL -lSDLmain -lglapp -framework Cocoa -framework OpenGL
	install_name_tool -change dist/osx/libGLApp.dylib ../dist/osx/libGLApp.dylib test

run: test
	./test

clean:
	-rm test
