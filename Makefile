OUTD=build
NAME=rlgl
SRC=src/rlgl.c
OBJ=$(patsubst %.c, %.o, $(SRC))
ifeq ($(OS), Windows_NT)
	CC=cl
	LIBEXT=dll
	FLAGS=-lopengl32 -lgdi32
else
	UNAME_S:=$(shell uname -s)
	CC=clang
	ifeq ($(UNAME_S), Darwin)
		LIBEXT=dylib
		FLAGS=-framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -Wno-deprecated-declarations
	else
		LIBEXT=so
		FLAGS=-lgl
	endif
endif
OPTS=-Wno-everything -Wno-deprecated-declarations -DGL_SILENCE_DEPRECATION
LIB=$(OUTD)/lib$(NAME).$(LIBEXT)

default: $(OUTD) $(LIB)

$(OUTD):
	mkdir $(OUTD)

$(LIB): $(OBJ)
	$(CC) -Isrc/ $(FLAGS) $(OPTS) -o $@ -shared -fpic $^

test: $(LIB)
	$(CC) test.c -Lbuild/ -lrlgl -lglfw

$(OBJ): %.o : %.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(OUTD) 

.PHONY: default clean test
