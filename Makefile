CXX:=g++
LDLIBS:=$$(pkg-config --libs ncurses)
CXXFLAGS += -std=c++20
LDFLAGS:=

ifeq (${DEBUG}, 1)
  CXXFLAGS += -O0 -ggdb -Wall -Wextra -Wpedantic
endif

COMP:=${CXX} ${CXXFLAGS} ${LDFLAGS} ${LDLIBS}

OUTPUT:=bsleep

main:
	${COMP} src/main.cpp -o ${OUTPUT}

install: main
	cp ${OUTPUT} /usr/bin

uninstall:
	rm /usr/bin/${OUTPUT}
