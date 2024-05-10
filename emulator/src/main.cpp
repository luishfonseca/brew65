#include <brew65emu/interface/panel.h>
#include <brew65emu/components/io_decoder.h>
#include <brew65emu/components/memory.h>

#include <emscripten.h>
#include <bitset>

brew65emu::interface::Renderer renderer(1280, 728);
brew65emu::interface::Panel panel(renderer);

brew65emu::components::IO_Decoder io_decoder;
brew65emu::components::Memory memory;

int PC = 0x0000;
std::bitset<16> ADDR_BUS;
std::bitset<8> DATA_BUS;
std::bitset<8> IO_BUS;

void update()
{
    PC = rand() % 0x10000;
    ADDR_BUS = rand();

    DATA_BUS = 0;
    IO_BUS = 0;

    memory.update(DATA_BUS, ADDR_BUS, false, true);
    io_decoder.update(IO_BUS, ADDR_BUS);
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, false, false);

    panel.update_pc(PC);
    panel.update_addr_bus(ADDR_BUS);
    panel.update_data_bus(DATA_BUS);
    panel.update_io_bus(IO_BUS);
    panel.update_ram(memory.get_ram());
    panel.update_bank(memory.get_active_bank(), memory.is_in_irq_or_reset(), memory.get_ram(), memory.get_flash());

    renderer.render();
}

int main(int argc, char *argv[])
{
    panel.init();

    for (int i = 0; i < 64 * 1024; i++)
    {
        DATA_BUS = rand();
        memory.update(DATA_BUS, i, true, false);
    }

    emscripten_set_main_loop(update, 0, 1);
    return 0;
}
