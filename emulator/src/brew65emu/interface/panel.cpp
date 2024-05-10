#include <brew65emu/interface/panel.h>

#include <bitset>

using namespace brew65emu::interface;

void Panel::init()
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1024, 0, 256, 728);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 728; j++)
        {
            this->renderer.update_pixel(pixels, i, j, 0xFFC0C0C0);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 728; j++)
        {
            this->renderer.update_pixel(pixels, i, j, 0xFFC0C0C0);
        }
    }
    this->renderer.update_end();
}

void Panel::update_pc(int pc)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 4, 128, 8);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                this->renderer.update_pixel(pixels, k + 8 * i, j, pc & (0b01 << i) ? 0xFFFF0000 : 0xFF000000);
            }
        }
    }
    this->renderer.update_end();
}

void Panel::update_addr_bus(const std::bitset<16> &addr_bus)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 16, 128, 8);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                this->renderer.update_pixel(pixels, k + 8 * i, j, addr_bus[i] ? 0xFF00FF00 : 0xFF000000);
            }
        }
    }
    this->renderer.update_end();
}

void Panel::update_data_bus(const std::bitset<8> &data_bus)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 28, 128, 16);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                this->renderer.update_pixel(pixels, k + 16 * i, j, data_bus[i] ? 0xFF0000FF : 0xFF000000);
            }
        }
    }
    this->renderer.update_end();
}

void Panel::update_io_bus(const std::bitset<8> &io_bus)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 306, 128, 16);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                this->renderer.update_pixel(pixels, k + 16 * i, j, io_bus[i] ? 0xFF00FF00 : 0xFF000000);
            }
        }
    }
    this->renderer.update_end();
}

void Panel::update_ram(const std::vector<uint8_t> &ram)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 48, 128, 254);
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 254; j++)
        {
            this->renderer.update_pixel(pixels, i, j,
                                        0xFF000000 |
                                            (ram[j * 128 + i] & 0b11100000) << 16 |
                                            (ram[j * 128 + i] & 0b00011100) << 11 |
                                            (ram[j * 128 + i] & 0b00000011) << 6);
        }
    }

    this->renderer.update_end();
}

void Panel::update_bank(int bank, bool irq_reset, const std::vector<uint8_t> &ram, const std::vector<uint8_t> &flash)
{
    uint32_t *pixels;
    this->renderer.update_start(&pixels, 1028, 326, 128, 254);
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 254; j++)
        {
            this->renderer.update_pixel(pixels, i, j,
                                        0xFF000000 |
                                            ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b11100000) << 16 |
                                            ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b00011100) << 11 |
                                            ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b00000011) << 6);
        }
    }
    this->renderer.update_end();

    this->renderer.update_start(&pixels, 1028, 584, 128, 32);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                for (int l = 0; l < 16; l++)
                {
                    uint32_t active_color = irq_reset ? 0xFFFFFF00 : 0xFF00FF00;
                    this->renderer.update_pixel(pixels, k + 16 * j, l + 16 * i, i * 8 + j == bank ? active_color : 0xFF000000);
                }
            }
        }
    }
    this->renderer.update_end();
}
