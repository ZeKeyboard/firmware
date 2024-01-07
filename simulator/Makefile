KEYBOARD_LAYOUT_JSON = ../submodules/scripts/resources/keyboard-layout.json
EXTRA_LEDS_JSON = submodules/scripts/resources/extra_leds.json
PYTHON = python3
GENERATE_LAYOUT = ../submodules/scripts/generate_layout.py

CXX = g++
CXX_FLAGS = -c -g -Wall -Wextra -std=gnu++23
SOURCES = $(wildcard *.cpp) $(wildcard **/*.cpp) $(wildcard ../core/*.cpp) $(wildcard ../core/**/*.cpp) $(wildcard ../common/*.cpp) $(wildcard ../common/**/*.cpp)
HEADERS = $(wildcard *.h) $(wildcard **/*.h) $(wildcard ../core/*.h) $(wildcard ../core/**/*.h) $(wildcard ../generated/*.h) $(wildcard ../common/*.h) $(wildcard ../common/**/*.h)

TARGETS = $(patsubst %.cpp,obj/%.o,$(SOURCES))

INCLUDE_LIBS = -I/usr/include/SFML
LINK_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: simulator

../generated/hardware_layout.h: $(KEYBOARD_LAYOUT_JSON) $(GENERATE_LAYOUT)
	mkdir -p $(@D)
	$(PYTHON) $(GENERATE_LAYOUT) -i $(KEYBOARD_LAYOUT_JSON) -e $(EXTRA_LEDS_JSON) -l cpp -o $@

obj/%.o: %.cpp $(HEADERS) ../generated/hardware_layout.h
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $< -o $@ $(INCLUDE_LIBS)

simulator: $(TARGETS)
	$(CXX) $(TARGETS) -o $@ $(LINK_FLAGS)

clean:
	rm -rf obj
	rm -f simulator
	rm -rf ../generated

