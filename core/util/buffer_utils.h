#pragma once


namespace core::util
{

/**
 * @brief Converts a buffer containing characters 0-9 and A-F to a buffer containing the corresponding hex values.
 * 
 */
void ascii_buffer_to_hex_buffer(const char* ascii_buffer,
                                char*& hex_buffer,
                                int ascii_buffer_size,
                                int& hex_buffer_size);

}
