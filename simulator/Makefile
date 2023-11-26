CXX = g++
CXX_FLAGS = -c -O2 -g -Wall -Wextra -std=gnu++17
SOURCES = $(wildcard *.cpp) $(wildcard **/*.cpp)$(wildcard ../core/*.cpp) $(wildcard ../core/**/*.cpp)
HEADERS = $(wildcard *.h) $(wildcard **/*.h) $(wildcard ../core/*.h) $(wildcard ../core/**/*.h)

TARGETS = $(patsubst %.cpp,obj/%.o,$(SOURCES))

INCLUDE_LIBS = -I/usr/include/SDL2

all: simulator

obj/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $< -o $@ $(INCLUDE_LIBS)

simulator: $(TARGETS)
	$(CXX) $(TARGETS) -o $@ `sdl2-config --cflags --libs`

clean:
	rm -rf obj
	rm -f simulator

