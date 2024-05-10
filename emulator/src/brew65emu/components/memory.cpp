#include <brew65emu/components/memory.h>

using namespace brew65emu::components;

void Memory::update(std::bitset<8> &data_bus, const std::bitset<16> &addr_bus, bool write_enable, bool output_enable)
{
    unsigned long addr = addr_bus.to_ulong();
    if (addr >> 8 == 0x7F) // IO
    {
        return;
    }

    if (addr > 32 * 1024)
    {
        addr |= this->bank & 0b111 << 15;
    }

    if (write_enable)
    {
        if (addr < 32 * 1024 - 256 || this->bank & 0b1000)
        {
            this->ram[addr] = data_bus.to_ulong();
        }
        else
        {
            this->flash[addr - 0x8000] = data_bus.to_ulong();
        }
    }

    if (output_enable)
    {
        if (addr < 32 * 1024 - 256 || this->bank & 0b1000)
        {
            data_bus = this->ram[addr];
        }
        else
        {
            data_bus = this->flash[addr - 0x8000];
        }
    }
}

void Memory::update_bank(const std::bitset<16> &addr_bus, const std::bitset<8> &data_bus, const std::bitset<8> &io_bus, bool irq, bool reset)
{
    if ((irq || reset) && !this->irq_reset)
    {
        this->irq_reset = true;
        this->prev_bank = this->bank;
        this->bank = 0;
    }

    bool io = io_bus[7] && io_bus[3];
    if (this->irq_reset && io && addr_bus[3]) // 7FF8 Enable Banking
    {
        this->bank = this->prev_bank;
        this->irq_reset = false;
    }
    if (io && !addr_bus[3]) // 7FF0 Set Bank
    {
        this->bank = data_bus.to_ulong() & 0b1111;
    }
}

const std::vector<uint8_t> &Memory::get_ram()
{
    return this->ram;
}

const std::vector<uint8_t> &Memory::get_flash()
{
    return this->flash;
}

int Memory::get_active_bank()
{
    return this->bank;
}

bool Memory::is_in_irq_or_reset()
{
    return this->irq_reset;
}
