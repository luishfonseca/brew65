#pragma once

#include "renderer.h"

namespace brew65emu::interface
{
    class Panel
    {
    public:
        Panel(Renderer &renderer) : renderer(renderer) {}

        void init();

        void update_pc(int pc);
        void update_addr_bus(uint16_t addr_bus);
        void update_data_bus(uint8_t data_bus);
        void update_io_bus(uint8_t io_bus);

        void update_ram(const std::vector<uint8_t> &ram);
        void update_bank(int bank, bool irq_reset, const std::vector<uint8_t> &ram, const std::vector<uint8_t> &flash);

    private:
        Renderer &renderer;
    };
}
