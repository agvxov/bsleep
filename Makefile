CXX:=g++
CFLAGS:=-O0 -ggdb -std=c++17
LDLIBS:=$$(pkg-config --libs ncurses)
LDFLAGS:=
COMP:=$(CXX) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

OUTPUT:=bsleep

main:
	${COMP} src/main.cpp -o ${OUTPUT}
