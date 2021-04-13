/** @file SSD1306.cpp.c
*   @brief Created on 2021-03-15 by Ben
*/
/**********************************************************************
* Includes
**********************************************************************/
#include "SSD1306.h"
#include "i2c.h"
#include <algorithm>

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/

/**********************************************************************
* Module Preprocessor Macros
**********************************************************************/

namespace control
{
    constexpr std::uint8_t cmd_single  = 0x80;
    constexpr std::uint8_t cmd_stream  = 0x00;
    constexpr std::uint8_t data_stream = 0x40;
    constexpr std::uint8_t data_single = 0xC0;
}

namespace commands
{
    namespace fundamental
    {
        constexpr std::uint8_t set_contrast_control = 0x81;
        constexpr std::uint8_t display_from_ram     = 0xA4;
        constexpr std::uint8_t entire_display_on    = 0xA5;
        constexpr std::uint8_t set_normal_display   = 0xA6;
        constexpr std::uint8_t set_inverted_display = 0xA7;
        constexpr std::uint8_t set_display_off      = 0xAE;
        constexpr std::uint8_t set_display_on       = 0xAF;
    }

    namespace scrolling
    {
        constexpr std::uint8_t right_horizontal_scroll   = 0x26;
        constexpr std::uint8_t left_horizontal_scroll    = 0x27;
        constexpr std::uint8_t vertical_and_right_scroll = 0x29;
        constexpr std::uint8_t vertical_and_left_scroll  = 0x2A;
        constexpr std::uint8_t deactivate_scroll         = 0x2E;
        constexpr std::uint8_t activate_scroll           = 0x2F;
        constexpr std::uint8_t set_vertical_scroll_area  = 0xA3;
    }

    namespace addressing
    {
        constexpr std::uint8_t set_addressing_mode = 0x20;
        constexpr std::uint8_t set_column_address  = 0x21;
        constexpr std::uint8_t set_page_address    = 0x22;

        constexpr std::uint8_t addressing_mode_horizontal = 0x0;
        constexpr std::uint8_t addressing_mode_vertical   = 0x1;
        constexpr std::uint8_t addressing_mode_page       = 0x2;
    }

    namespace hardware_config
    {
        constexpr std::uint8_t segment_remap_0_start   = 0xA0;
        constexpr std::uint8_t segment_remap_127_start = 0xA1;
        constexpr std::uint8_t set_multiplex_ratio     = 0xA8;
        constexpr std::uint8_t set_COM_low_to_high     = 0xC0;
        constexpr std::uint8_t set_COM_high_to_low     = 0xC8;
        constexpr std::uint8_t set_display_offset      = 0xD3;
        constexpr std::uint8_t set_COM_pin_config      = 0xDA;
    }

    namespace timing
    {
        constexpr std::uint8_t set_clk_divide_ratio  = 0xD5;
        constexpr std::uint8_t set_pre_charge_period = 0xD9;
        constexpr std::uint8_t set_v_comh_level      = 0xDB;
        constexpr std::uint8_t nop                   = 0xE3;
    }

    namespace charge_pump
    {
        constexpr std::uint8_t setting = 0x8D;
    }
}

/**********************************************************************
* Module Typedefs
**********************************************************************/

/*********************************************************************
* Module Variable Definitions
**********************************************************************/
uint8_t lineBuffer[129];

static I2C_Channel channel;
static uint8_t address;


/**********************************************************************
* Function Prototypes
**********************************************************************/
static void set_address(uint8_t page_idx, uint8_t column_idx);

/**********************************************************************
* Function Definitions
**********************************************************************/


void ssd1306_init(uint8_t slaveAddress, I2C_Channel i2CChannel)
{
    channel      = i2CChannel;
    address = slaveAddress;

    static const uint8_t initCommands[] =
    {
        control::cmd_stream,
        commands::fundamental::set_display_off,
        commands::timing::set_clk_divide_ratio, 0x80,
        commands::hardware_config::set_multiplex_ratio, 0x1f,
        commands::hardware_config::set_display_offset, 0x00,
        0x40, /* Set Display Start Line to 0 */
        commands::charge_pump::setting, 0x14,
        commands::addressing::set_addressing_mode, commands::addressing::addressing_mode_page,
        commands::hardware_config::segment_remap_127_start,
        commands::hardware_config::set_COM_high_to_low,
        commands::hardware_config::set_COM_pin_config, 0x02,
        commands::fundamental::set_contrast_control, 0x8f,
        commands::timing::set_pre_charge_period, 0xf1,
        commands::timing::set_v_comh_level, 0x40,
        commands::fundamental::display_from_ram,
        commands::fundamental::set_normal_display,
        commands::scrolling::deactivate_scroll,
        commands::fundamental::set_display_on,
    };

    i2c_write(channel, slaveAddress, initCommands, sizeof(initCommands), true);
    ssd1306_clear_display();
}

void ssd1306_clear_display()
{
    lineBuffer[0] = control::data_stream;
    std::fill(&lineBuffer[1], &lineBuffer[128], 0x00);
    for (int i = 0; i < 8; ++i)
    {
        set_address(i, 0);
        i2c_write(channel, address, lineBuffer, sizeof(lineBuffer), true);
    }
}

void set_address(uint8_t page_idx, uint8_t column_idx)
{
    uint8_t setAddrCMD[] =
    {
        control::cmd_stream,
        static_cast<uint8_t>(0xB0 | page_idx),      /* Set to page 0     */
        static_cast<uint8_t>(0x00 | (column_idx & 0x0F)),
        static_cast<uint8_t>(0x10 | (column_idx & 0xF0) >> 4) /* Start at column 0 */
    };
    i2c_write(channel, address, setAddrCMD, sizeof(setAddrCMD), true);
}

void ssd1306_write_string(const char *string, uint8_t line, uint8_t charPos)
{
    set_address(line, charPos*8);
    uint8_t * buffer = lineBuffer;
    *buffer = control::data_stream;
    buffer++;

    uint8_t i;
    const char* c;
    for (c=string, i=0; *c != '\0'; c++, i++)
    {
        const uint8_t* charFont = CharTable[*c-32];
        *buffer++ = 0;
        std::copy(charFont, charFont+5, buffer);
        buffer += 5;
        *buffer++ = 0;
        *buffer++ = 0;
    }
    i2c_write(channel, address, lineBuffer, i*8 + 1, true);
}

void ssd1306_write_char(const uint8_t *charTable, uint8_t line, uint8_t charPos)
{
    set_address(line, charPos*8);
    uint8_t * buffer = lineBuffer;
    *buffer++ = control::data_stream;
    *buffer++ = 0;
    std::copy(charTable, charTable+5, buffer);
    buffer += 5;
    *buffer++ = 0;
    *buffer++ = 0;
    i2c_write(channel, address, lineBuffer, 9, true);
}
