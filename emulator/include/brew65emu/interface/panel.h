#pragma once

#include "renderer.h"

namespace brew65emu::interface
{
    class Panel
    {
    public:
        Panel(Renderer &renderer) : renderer(renderer) {}

        void init();

        void update_pc(uint16_t pc);
        void update_sp(uint8_t sp);
        void update_a(uint8_t a);
        void update_x(uint8_t x);
        void update_y(uint8_t y);
        void update_status(uint8_t status);
        void update_addr_bus(uint16_t addr_bus);
        void update_data_bus(uint8_t data_bus);
        void update_io_bus(uint8_t io_bus);

        void update_ram(const uint8_t *ram);
        void update_bank(int bank, bool irq_reset, const uint8_t *ram, const uint8_t *flash);

    private:
        Renderer &renderer;
    };
}
