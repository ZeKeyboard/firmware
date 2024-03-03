#pragma once

#include <cstdint>
#include <stdint.h>


enum class PinMode
{
    IN = 0,
    OUT = 1,
    IN_PULLUP = 2,
    IN_PULLDOWN = 3,
    OUT_OPENDRAIN = 4,
    IN_DISABLE = 5,
};

enum class PinState
{
    LEVEL_LOW = 0,
    LEVEL_HIGH = 1,
};

class Device
{
public:
    virtual void sleep_millis(const int millis) = 0;
    virtual void sleep_micros(const int micros) = 0;
    virtual void gpio_setup(const uint8_t pin, const PinMode mode) = 0;
    virtual void gpio_write(const uint8_t pin, const PinState value) = 0;
    virtual PinState gpio_read(const uint8_t pin) = 0;

    virtual void set_keyboard_key1(const uint8_t code) = 0;
    virtual void set_keyboard_key2(const uint8_t code) = 0;
    virtual void set_keyboard_key3(const uint8_t code) = 0;
    virtual void set_keyboard_key4(const uint8_t code) = 0;
    virtual void set_keyboard_key5(const uint8_t code) = 0;
    virtual void set_keyboard_key6(const uint8_t code) = 0;
    virtual void set_keyboard_modifier(const uint16_t modifier) = 0;
    virtual void set_keyboard_media(const uint16_t media) = 0;
    virtual void keyboard_send() = 0;

    /**
     * Initialize the SD card.
     * 
     * @return true if the SD card was initialized successfully, false otherwise.
     */
    virtual bool sd_init() = 0;
    /**
     * Read the contents of a file from the SD card.
     * 
     * @param filename The name of the file to read.
     * @param buffer A pointer to a buffer that will be allocated and filled with the contents of the file. Remember to delete[] this buffer when you're done with it.
     * @param num_read_bytes The number of bytes read from the file.
     * 
     * @return true if the file was read successfully, false otherwise.
     */
    virtual bool sd_read(const char* filename, char*& buffer, uint32_t& num_read_bytes) const = 0;
    /**
     * Write the contents of a buffer to a file on the SD card.
     * 
     * @param filename The name of the file to write to.
     * @param buffer A pointer to the buffer containing the data to write.
     * @param num_bytes The number of bytes to write to the file.
     * 
     * @return true if the file was written successfully, false otherwise.
     */
    virtual bool sd_write(const char* filename, const char* buffer, const uint32_t num_bytes) = 0;

    virtual uint16_t get_keyboard_leds() = 0;

    virtual void serial_begin(const uint32_t baud) = 0;
    virtual void serial_print(const char* str) = 0;

    virtual void serial_print(uint8_t val) = 0;
    virtual void serial_print(uint16_t val) = 0;
    virtual void serial_print(uint32_t val) = 0;
    virtual void serial_print(int8_t val) = 0;
    virtual void serial_print(int16_t val) = 0;
    virtual void serial_print(int32_t val) = 0;

    virtual void serial_println(const char* str) = 0;
    virtual void serial_println(uint8_t val) = 0;
    virtual void serial_println(uint16_t val) = 0;
    virtual void serial_println(uint32_t val) = 0;
    virtual void serial_println(int8_t val) = 0;
    virtual void serial_println(int16_t val) = 0;
    virtual void serial_println(int32_t val) = 0;

    virtual void start_timer() = 0;
    virtual uint32_t get_timer_micros() = 0;

    /**
     * Milliseconds since the device was started.
     */
    virtual uint32_t milliseconds_since_start() const = 0;

    virtual void set_led(uint16_t index, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void update_leds() = 0;

    inline void set_keyboard_key_by_index(const uint8_t index, const uint8_t code)
    {
        // This is a bit of a hack, but it works.
        if (index == 0)
        {
            set_keyboard_key1(code);
        }
        else if (index == 1)
        {
            set_keyboard_key2(code);
        }
        else if (index == 2)
        {
            set_keyboard_key3(code);
        }
        else if (index == 3)
        {
            set_keyboard_key4(code);
        }
        else if (index == 4)
        {
            set_keyboard_key5(code);
        }
        else if (index == 5)
        {
            set_keyboard_key6(code);
        }
    }
};
