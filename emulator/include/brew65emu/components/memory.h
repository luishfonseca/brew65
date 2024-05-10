#pragma once

#include <vector>

namespace brew65emu::components
{
    class Memory
    {
    public:
        void update(uint8_t &data_bus, uint16_t addr_bus, bool write_enable, bool output_enable);
        void update_bank(uint16_t addr_bus, uint8_t data_bus, uint8_t io_bus, bool irq, bool reset);

        std::vector<uint8_t> &get_ram();
        std::vector<uint8_t> &get_flash();
        int get_active_bank();
        bool is_in_irq_or_reset();

    private:
        std::vector<uint8_t> ram = std::vector<uint8_t>(512 * 1024, 0x00);
        std::vector<uint8_t> flash = std::vector<uint8_t>(256 * 1024, 0x00);

        int prev_bank = 0;
        bool irq_reset = false;

        int bank = 0;
    };
}