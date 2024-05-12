#pragma once

#include <vector>

namespace brew65emu::components
{
    class Memory
    {
    public:
        void update(uint8_t &data_bus, uint16_t addr_bus, bool write_enable, bool output_enable);
        void update_bank(uint16_t addr_bus, uint8_t data_bus, uint8_t io_bus, bool irq, bool reset);

        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

        const uint8_t *get_ram();
        const uint8_t *get_flash();
        int get_active_bank();
        bool is_in_irq_or_reset();

    private:
        uint8_t ram[512 * 1024] = {0x00};
        uint8_t flash[256 * 1024] = {0x00};

        int prev_bank = 0;
        bool irq_reset = false;

        int bank = 0;
    };
}