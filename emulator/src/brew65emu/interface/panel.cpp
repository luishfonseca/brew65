#include <brew65emu/interface/panel.h>

using namespace brew65emu::interface;

void Panel::init()
{
    std::vector<uint8_t> pixels(256 * 728, 0x92);
    this->renderer.draw_pixels(pixels.data(), 1024, 0, 256, 728);

    this->renderer.draw_text("PC", 1156, 0, 14, 0xFF);
    this->renderer.draw_text("SP", 1156, 16, 14, 0xFF);
    this->renderer.draw_text("A", 1156, 36, 14, 0xFF);
    this->renderer.draw_text("X", 1156, 56, 14, 0xFF);
    this->renderer.draw_text("Y", 1156, 76, 14, 0xFF);
    this->renderer.draw_text("MA", 1156, 92, 14, 0xFF);
    this->renderer.draw_text("D", 1156, 108, 14, 0xFF);
    this->renderer.draw_text("IO", 1156, 386, 14, 0xFF);
    this->renderer.draw_text("BS", 1156, 672, 14, 0xFF);
    this->renderer.draw_text("P", 1156, 700, 14, 0xFF);
    this->renderer.draw_text(" N  V  1  B    D  I  Z  C", 1028, 714, 14, 0xFF);

    std::vector<uint8_t> pixel2(102 * 378, 0);
    this->renderer.draw_pixels(pixel2.data(), 1174, 4, 102, 378);

    std::vector<uint8_t> pixel3(102 * 712, 0);
    this->renderer.draw_pixels(pixel3.data(), 1174, 386, 102, 330);
}

void Panel::update_pc(uint16_t pc)
{
    std::vector<uint8_t> pixels(256 * 8, 0);
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if (pc & (0x8000 >> i))
                    pixels[j * 128 + i * 8 + k] = 0b11100000;
    this->renderer.draw_pixels(pixels.data(), 1028, 4, 128, 8);
}

void Panel::update_sp(uint8_t sp)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (sp & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b11100000;
    this->renderer.draw_pixels(pixels.data(), 1028, 16, 128, 16);
}

void Panel::update_a(uint8_t a)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (a & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b00000011;
    this->renderer.draw_pixels(pixels.data(), 1028, 36, 128, 16);
}

void Panel::update_x(uint8_t x)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (x & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b00000011;
    this->renderer.draw_pixels(pixels.data(), 1028, 56, 128, 16);
}

void Panel::update_y(uint8_t y)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (y & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b00000011;
    this->renderer.draw_pixels(pixels.data(), 1028, 76, 128, 16);
}

void Panel::update_addr_bus(uint16_t addr_bus)
{
    std::vector<uint8_t> pixels(128 * 8, 0);
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if (addr_bus & (0x8000 >> i))
                    pixels[j * 128 + i * 8 + k] = 0b00011100;
    this->renderer.draw_pixels(pixels.data(), 1028, 96, 128, 8);
}

void Panel::update_data_bus(uint8_t data_bus)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (data_bus & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b00000011;
    this->renderer.draw_pixels(pixels.data(), 1028, 108, 128, 16);
}

void Panel::update_io_bus(uint8_t io_bus)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (io_bus & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b00011100;
    this->renderer.draw_pixels(pixels.data(), 1028, 386, 128, 16);
}

void Panel::update_ram(const uint8_t *ram)
{
    std::vector<uint8_t> pixels(128 * 254);
    memcpy(pixels.data(), ram, 128 * 254);
    this->renderer.draw_pixels(pixels.data(), 1028, 128, 128, 254);
}

void Panel::update_bank(int bank, bool irq_reset, const uint8_t *ram, const uint8_t *flash)
{
    std::vector<uint8_t> pixels(128 * 254);
    memcpy(pixels.data(), (bank < 8 ? flash : ram) + bank * 32 * 1024, 128 * 254);
    this->renderer.draw_pixels(pixels.data(), 1028, 406, 128, 254);

    std::vector<uint8_t> pixels2(128 * 32, 0);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 16; k++)
                for (int l = 0; l < 16; l++)
                    if (i * 8 + j == bank)
                        pixels2[i * 128 * 16 + l * 128 + j * 16 + k] = irq_reset ? 0b11111100 : 0b00011100;
    this->renderer.draw_pixels(pixels2.data(), 1028, 664, 128, 32);
}

void Panel::update_status(uint8_t status)
{
    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (status & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b11100000;
    this->renderer.draw_pixels(pixels.data(), 1028, 700, 128, 16);
}
