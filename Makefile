ARDUINO_PATH = ${ARDUINO_DIR}
ARDUINO_PACKAGES = $(ARDUINO_PATH)/packages
TEENSY_DIR = $(ARDUINO_PACKAGES)/teensy
TEENSY_TOOLS = $(TEENSY_DIR)/tools
TEENSY_HARDWARE = $(TEENSY_DIR)/hardware

CATCH2_PATH = submodules/Catch2
CATCH2_INCLUDE = -I$(CATCH2_PATH)/extras

LIBRARIES_VERSION = 1.59.0
TEENSYDUINO_VERSION_FLAG = 159

TEENSY_AVR = $(TEENSY_HARDWARE)/avr/$(LIBRARIES_VERSION)
TEENSY_LIBS = $(TEENSY_AVR)/libraries
TEENSY4_CORE = $(TEENSY_AVR)/cores/teensy4

TEENSY_COMPILE_VERSION = 11.3.1
TEENSY_COMPILE = $(TEENSY_TOOLS)/teensy-compile/$(TEENSY_COMPILE_VERSION)/arm/bin

TEST_CXX = g++
TEST_CXX_FLAGS = -c -g -Wall -Wextra -std=gnu++23

CXX = $(TEENSY_COMPILE)/arm-none-eabi-g++
CC = $(TEENSY_COMPILE)/arm-none-eabi-gcc
AR = $(TEENSY_COMPILE)/arm-none-eabi-gcc-ar
SIZE = $(TEENSY_COMPILE)/arm-none-eabi-size
PRECOMPILE_HELPER = $(TEENSY_TOOLS)/teensy-tools/$(LIBRARIES_VERSION)/precompile_helper
OBJCOPY = $(TEENSY_COMPILE)/arm-none-eabi-objcopy
POST_COMPILE = $(TEENSY_TOOLS)/teensy-tools/$(LIBRARIES_VERSION)/teensy_post_compile
PYTHON = python3
GENERATE_LAYOUT = submodules/scripts/generate_layout.py

KEYBOARD_LAYOUT_JSON = submodules/scripts/resources/keyboard-layout.json
EXTRA_LEDS_JSON = submodules/scripts/resources/extra_leds.json

PRECOMPILE_FLAGS = -x c++-header -O2 -g -Wall -ffunction-sections -fdata-sections -nostdlib -MMD -std=gnu++17 -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -D__IMXRT1062__ -DTEENSYDUINO=$(TEENSYDUINO_VERSION_FLAG) -DARDUINO=10607 -DARDUINO_TEENSY41 -DF_CPU=600000000 -DUSB_SERIAL_HID -DLAYOUT_US_ENGLISH -I$(TEENSY4_CORE)

LINK_FLAGS = -O2 -Wl,--gc-sections,--relax -T$(TEENSY_HARDWARE)/avr/$(LIBRARIES_VERSION)/cores/teensy4/imxrt1062_t41.ld -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16

CXX_17 = -std=gnu++17
CORE_CXX_VERSION = -std=gnu++23

CXX_FLAGS = -c -O2 -g -Wall -Wextra -ffunction-sections -fdata-sections -nostdlib -MMD -fno-exceptions -fpermissive -fno-rtti -fno-threadsafe-statics -felide-constructors -Wno-error=narrowing -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -D__IMXRT1062__ -DTEENSYDUINO=$(TEENSYDUINO_VERSION_FLAG) -DARDUINO=10607 -DARDUINO_TEENSY41 -DF_CPU=600000000 -DUSB_SERIAL_HID -DLAYOUT_US_ENGLISH

CC_FLAGS = -c -O2 -g -Wall -ffunction-sections -fdata-sections -nostdlib -MMD -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -D__IMXRT1062__ -DTEENSYDUINO=$(TEENSYDUINO_VERSION_FLAG) -DARDUINO=10607 -DARDUINO_TEENSY41 -DF_CPU=600000000 -DUSB_SERIAL_HID -DLAYOUT_US_ENGLISH

OBJCOPY_FLAGS = -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0

LIB_SRC = FastLED/src SPI OctoWS2811 SD/src SdFat/src

LIB_PATHS = $(patsubst %,$(TEENSY_LIBS)/%,$(LIB_SRC)))

INCLUDE_LIBS = -Ibuild/pch -I$(TEENSY4_CORE) $(patsubst %,-I$(TEENSY_LIBS)/%,$(LIB_SRC))

FASTLED_HEADERS = $(wildcard $(TEENSY_LIBS)/FastLED/src/*.h)
SPI_HEADERS = $(wildcard $(TEENSY_LIBS)/SPI/*.h)
OCTOWS2811_HEADERS = $(wildcard $(TEENSY_LIBS)/OctoWS2811/*.h)
SD_HEADERS = $(wildcard $(TEENSY_LIBS)/SD/src/*.h)
SDFAT_HEADERS = $(wildcard $(TEENSY_LIBS)/SdFat/src/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/common/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/ExFatLib/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/FatLib/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/FsLib/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/SdCard/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/iostream/*.h) $(wildcard $(TEENSY_LIBS)/SdFat/src/SpiDriver/*.h)

CORE_HEADERS = $(wildcard $(TEENSY4_CORE)/*.h)
LIB_HEADERS = $(FASTLED_HEADERS) $(SPI_HEADERS) $(OCTOWS2811_HEADERS) $(SD_HEADERS) $(SDFAT_HEADERS)
NON_HARDWARE_HEADERS = $(wildcard core/*.h) $(wildcard core/**/*.h) $(wildcard core/**/**/*.h) $(wildcard common/*.h) $(wildcard common/**/*.h) $(wildcard generated/*.h)
HEADERS = $(wildcard *.h) $(NON_HARDWARE_HEADERS)

FASTLED_SOURCES = $(wildcard $(TEENSY_LIBS)/FastLED/src/*.cpp)
SPI_SOURCES = $(wildcard $(TEENSY_LIBS)/SPI/*.cpp)
OCTOWS2811_SOURCES = $(wildcard $(TEENSY_LIBS)/OctoWS2811/*.cpp)
SD_SOURCES = $(wildcard $(TEENSY_LIBS)/SD/src/*.cpp)
SDFAT_SOURCES = $(wildcard $(TEENSY_LIBS)/SdFat/src/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/common/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/ExFatLib/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/FatLib/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/FsLib/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/SdCard/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/iostream/*.cpp) $(wildcard $(TEENSY_LIBS)/SdFat/src/SpiDriver/*.cpp)

CORE_CPP_SOURCES = $(wildcard $(TEENSY4_CORE)/*.cpp)
CORE_C_SOURCES = $(wildcard $(TEENSY4_CORE)/*.c)
LIB_SOURCES = $(FASTLED_SOURCES) $(SPI_SOURCES) $(OCTOWS2811_SOURCES) $(SD_SOURCES) $(SDFAT_SOURCES)
NON_HARDWARE_SOURCES_NON_FILTERED = $(wildcard core/*.cpp) $(wildcard core/**/**/*.cpp) $(wildcard core/**/*.cpp) $(wildcard common/*.cpp) $(wildcard common/**/*.cpp) $(wildcard common/**/**/*.cpp)
TEST_CPP = $(wildcard core/test/*.cpp) $(wildcard core/**/test/*.cpp) $(CATCH2_PATH)/extras/catch_amalgamated.cpp
TEST_SOURCES = $(NON_HARDWARE_SOURCES) $(TEST_CPP)
NON_HARDWARE_SOURCES = $(filter-out $(TEST_CPP), $(NON_HARDWARE_SOURCES_NON_FILTERED))
SOURCES = $(wildcard *.cpp) $(NON_HARDWARE_SOURCES)

all: build/firmware.hex

generated/hardware_layout.h: $(KEYBOARD_LAYOUT_JSON) $(GENERATE_LAYOUT)
	mkdir -p $(@D)
	$(PYTHON) $(GENERATE_LAYOUT) -i $(KEYBOARD_LAYOUT_JSON) -e $(EXTRA_LEDS_JSON) -l cpp -o $@

build/pch/Arduino.h.gch:
	mkdir -p $(@D)
	$(PRECOMPILE_HELPER) $(TEENSY4_CORE) build/ $(CXX) $(PRECOMPILE_FLAGS) build/pch/Arduino.h -o build/pch/Arduino.h.gch

build/core/%.cpp.o: %.cpp $(CORE_HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(CXX_17) $(INCLUDE_LIBS) -c $< -o $@

build/core/%.c.o: %.c $(CORE_HEADERS)
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(TEENSY4_CORE) -c $< -o $@

CORE_C_TARGETS =  $(patsubst %.c,build/core/%.c.o,$(CORE_C_SOURCES))
CORE_CPP_TARGETS =  $(patsubst %.cpp,build/core/%.cpp.o,$(CORE_CPP_SOURCES))
build/core/core.a: $(CORE_CPP_TARGETS) $(CORE_C_TARGETS)
	@$(AR) rcs $@ $(CORE_CPP_TARGETS) $(CORE_C_TARGETS)

build/libraries/%.o: %.cpp $(LIB_HEADERS) build/pch/Arduino.h.gch
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(CXX_17) $(INCLUDE_LIBS) -c $< -o $@

build/%.o: %.cpp $(HEADERS) build/pch/Arduino.h.gch generated/hardware_layout.h
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(CORE_CXX_VERSION) $(INCLUDE_LIBS) -c $< -o $@

TARGETS = $(patsubst %.cpp,build/%.o,$(SOURCES)) $(patsubst %.cpp,build/libraries/%.o,$(LIB_SOURCES)) build/core/core.a

TEST_TARGETS = $(patsubst %.cpp,build/test/%.o,$(TEST_SOURCES))

build/firmware.elf: $(TARGETS)
	@$(CC) $(LINK_FLAGS) -o $@ $(TARGETS) build/core/core.a -Lbuild/ -larm_cortexM7lfsp_math -lm -lstdc++
	@echo
	@echo "Firmware size:"
	@$(SIZE) -B -d $@
	@echo

build/firmware.hex: build/firmware.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: build/firmware.hex
	teensy_loader_cli --mcu=TEENSY41 -w build/firmware.hex

build/test/%.o: %.cpp $(NON_HARDWARE_HEADERS) generated/hardware_layout.h
	mkdir -p $(@D)
	$(TEST_CXX) $(TEST_CXX_FLAGS) $< -o $@ $(CATCH2_INCLUDE)

test_main: $(TEST_TARGETS)
	$(TEST_CXX) $(TEST_TARGETS) -o $@

test: test_main
	./test_main

clean:
	rm -rf build/
	rm -rf generated/
	rm -rf test_main
