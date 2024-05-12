#include <brew65emu/interface/panel.h>

using namespace brew65emu::interface;

void Panel::init()
{
    std::vector<uint8_t> pixels(256 * 728, 0x92);
    this->renderer.draw_pixels(pixels.data(), 1024, 0, 256, 728);
}

void Panel::update_pc(uint16_t pc)
{
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 4, 128, 8);
    // for (int i = 0; i < 16; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         for (int k = 0; k < 8; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 8 * i, j, pc & (0x8000 >> i) ? 0xFFFF0000 : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

    std::vector<uint8_t> pixels(256 * 728, 0);
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if (pc & (0x8000 >> i))
                    pixels[j * 128 + i * 8 + k] = 0b11100000;
    this->renderer.draw_pixels(pixels.data(), 1028, 4, 128, 8);
}

void Panel::update_sp(uint8_t sp)
{
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 16, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, sp & (0x80 >> i) ? 0xFFFF0000 : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 36, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, a & (0x80 >> i) ? 0xFF0000FF : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 56, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, x & (0x80 >> i) ? 0xFF0000FF : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 76, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, y & (0x80 >> i) ? 0xFF0000FF : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 96, 128, 8);
    // for (int i = 0; i < 16; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         for (int k = 0; k < 8; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 8 * i, j, addr_bus & (0x8000 >> i) ? 0xFF00FF00 : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 108, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, data_bus & (0x80 >> i) ? 0xFF0000FF : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 386, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, io_bus & (0x80 >> i) ? 0xFF00FF00 : 0xFF000000);
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 128, 128, 254);
    // for (int i = 0; i < 128; i++)
    // {
    //     for (int j = 0; j < 254; j++)
    //     {
    //         this->renderer.update_pixel(pixels, i, j,
    //                                     0xFF000000 |
    //                                         (ram[j * 128 + i] & 0b11100000) << 16 |
    //                                         (ram[j * 128 + i] & 0b00011100) << 11 |
    //                                         (ram[j * 128 + i] & 0b00000011) << 6);
    //     }
    // }

    // this->renderer.update_end();

    std::vector<uint8_t> pixels(128 * 254);
    memcpy(pixels.data(), ram, 128 * 254);
    this->renderer.draw_pixels(pixels.data(), 1028, 128, 128, 254);
}

void Panel::update_bank(int bank, bool irq_reset, const uint8_t *ram, const uint8_t *flash)
{
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 406, 128, 254);
    // for (int i = 0; i < 128; i++)
    // {
    //     for (int j = 0; j < 254; j++)
    //     {
    //         this->renderer.update_pixel(pixels, i, j,
    //                                     0xFF000000 |
    //                                         ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b11100000) << 16 |
    //                                         ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b00011100) << 11 |
    //                                         ((bank < 8 ? flash : ram)[bank * 32 * 1024 + j * 128 + i] & 0b00000011) << 6);
    //     }
    // }
    // this->renderer.update_end();

    std::vector<uint8_t> pixels(128 * 254);
    memcpy(pixels.data(), (bank < 8 ? flash : ram) + bank * 32 * 1024, 128 * 254);
    this->renderer.draw_pixels(pixels.data(), 1028, 406, 128, 254);

    // this->renderer.update_start(&pixels, 1028, 664, 128, 32);
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             for (int l = 0; l < 16; l++)
    //             {
    //                 uint32_t active_color = irq_reset ? 0xFFFFFF00 : 0xFF00FF00;
    //                 this->renderer.update_pixel(pixels, k + 16 * j, l + 16 * i, i * 8 + j == bank ? active_color : 0xFF000000);
    //             }
    //         }
    //     }
    // }
    // this->renderer.update_end();

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
    // uint32_t *pixels;
    // this->renderer.update_start(&pixels, 1028, 700, 128, 16);
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 16; j++)
    //     {
    //         for (int k = 0; k < 16; k++)
    //         {
    //             this->renderer.update_pixel(pixels, k + 16 * i, j, status & (0x80 >> i) ? 0xFFFF0000 : 0xFF000000);
    //         }
    //     }
    // }

    std::vector<uint8_t> pixels(128 * 16, 0);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (status & (0x80 >> i))
                    pixels[j * 128 + i * 16 + k] = 0b11100000;
    this->renderer.draw_pixels(pixels.data(), 1028, 700, 128, 16);
}
