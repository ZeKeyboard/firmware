#include "key_properties.h"
#include "../generated/hardware_layout.h"

namespace common
{

const LEDDescription& KeyDescription::get_associated_led() const
{
    return constants::LED_PROPERTIES[led_strip_index];
}

}
