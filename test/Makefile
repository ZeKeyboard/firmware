CXX = g++
CXX_FLAGS = -c -g -Wall -Wextra -std=gnu++23

CATCH2_PATH = ${CATCH_DIR}
CATCH2_INCLUDE = -I$(CATCH2_PATH)/extras

SOURCES = $(wildcard *.cpp) $(wildcard **/*.cpp) $(wildcard ../core/*.cpp) $(wildcard ../core/**/*.cpp) $(wildcard ../common/*.cpp) $(wildcard ../common/**/*.cpp)

TEST_SOURCES = $(wildcard ../core/test/*.cpp) $(wildcard ../core/**/test/*.cpp) $(CATCH2_PATH)/extras/catch_amalgamated.cpp

ALL_SOURCES = $(SOURCES) $(TEST_SOURCES)

HEADERS = $(wildcard *.h) $(wildcard **/*.h) $(wildcard ../core/*.h) $(wildcard ../core/**/*.h) $(wildcard ../generated/*.h) $(wildcard ../common/*.h) $(wildcard ../common/**/*.h)

TARGETS = $(patsubst %.cpp,build/%.o,$(ALL_SOURCES))

runtests: test
	./test

build/%.o: %.cpp $(HEADERS) ../generated/hardware_layout.h
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $< -o $@ $(CATCH2_INCLUDE)

test: $(TARGETS)
	$(CXX) $(TARGETS) -o $@

clean:
	rm -rf build/
	rm -rf core/
	rm test
