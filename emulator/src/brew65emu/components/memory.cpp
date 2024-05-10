#include <brew65emu/components/memory.h>

using namespace brew65emu::components;

void Memory::update(uint8_t &data_bus, uint16_t addr_bus, bool write_enable, bool output_enable)
{
    if (addr_bus >> 8 == 0x7F) // IO
    {
        return;
    }

    if (addr_bus > 32 * 1024)
    {
        addr_bus |= this->bank & 0b111 << 15;
    }

    if (write_enable)
    {
        if (addr_bus < 32 * 1024 - 256 || this->bank & 0b1000)
        {
            this->ram[addr_bus] = data_bus;
        }
        else
        {
            this->flash[addr_bus - 0x8000] = data_bus;
        }
    }

    if (output_enable)
    {
        if (addr_bus < 32 * 1024 - 256 || this->bank & 0b1000)
        {
            data_bus = this->ram[addr_bus];
        }
        else
        {
            data_bus = this->flash[addr_bus - 0x8000];
        }
    }
}

void Memory::update_bank(uint16_t addr_bus, uint8_t data_bus, uint8_t io_bus, bool irq, bool reset)
{
    if ((irq || reset) && !this->irq_reset)
    {
        this->irq_reset = true;
        this->prev_bank = this->bank;
        this->bank = 0;
    }

    bool io = (io_bus & 0b10000000) && (io_bus & 0b00001000);
    if (this->irq_reset && io && (addr_bus & 0b00001000)) // 7FF8 Enable Banking
    {
        this->bank = this->prev_bank;
        this->irq_reset = false;
    }
    if (io && !(addr_bus & 0b00001000)) // 7FF0 Set Bank
    {
        this->bank = data_bus & 0b1111;
    }
}

std::vector<uint8_t> &Memory::get_ram()
{
    return this->ram;
}

std::vector<uint8_t> &Memory::get_flash()
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
