#include <brew65emu/interface/panel.h>
#include <brew65emu/components/io_decoder.h>
#include <brew65emu/components/memory.h>

#include <mos6502.h>

#include <emscripten.h>
#include <iostream>

brew65emu::interface::Renderer renderer(1280, 728);
brew65emu::interface::Panel panel(renderer);

brew65emu::components::IO_Decoder io_decoder;
brew65emu::components::Memory memory;

uint8_t read(uint16_t addr);
void write(uint16_t addr, uint8_t data);
mos6502 cpu(read, write);

uint16_t ADDR_BUS = 0;
uint8_t DATA_BUS = 0;
uint8_t IO_BUS = 0;

uint8_t read(uint16_t addr)
{
    ADDR_BUS = addr;
    memory.update(DATA_BUS, ADDR_BUS, false, true);
    io_decoder.update(IO_BUS, ADDR_BUS);
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, false, false);
    return DATA_BUS;
}

void write(uint16_t addr, uint8_t data)
{
    ADDR_BUS = addr;
    DATA_BUS = data;
    memory.update(DATA_BUS, ADDR_BUS, true, false);
    io_decoder.update(IO_BUS, ADDR_BUS);
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, false, false);
}

void reset()
{
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, false, true);
    cpu.Reset();
}

void irq()
{
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, true, false);
    cpu.IRQ();
}

void nmi()
{
    memory.update_bank(ADDR_BUS, DATA_BUS, IO_BUS, true, false);
    cpu.NMI();
}

void panel_update()
{
    panel.update_pc(cpu.GetPC());
    panel.update_sp(cpu.GetS());
    panel.update_a(cpu.GetA());
    panel.update_x(cpu.GetX());
    panel.update_y(cpu.GetY());
    panel.update_status(cpu.GetP());
    panel.update_addr_bus(ADDR_BUS);
    panel.update_data_bus(DATA_BUS);
    panel.update_io_bus(IO_BUS);
    panel.update_ram(memory.get_ram());
    panel.update_bank(memory.get_active_bank(), memory.is_in_irq_or_reset(), memory.get_ram(), memory.get_flash());

    renderer.render();
}

void update()
{
    ADDR_BUS = 0;
    DATA_BUS = 0;
    IO_BUS = 0;

    uint64_t c = 0;
    cpu.Run(1, c);

    panel_update();
}

int main(int argc, char *argv[])
{
#ifndef NDEBUG
    EM_ASM(console.log("Table: ", wasmTable););
#endif

    panel.init();

    for (int i = 0; i < 64 * 1024; i++)
    {
        DATA_BUS = rand();
        memory.update(DATA_BUS, i, true, false);
    }

    reset();
    panel_update();
    emscripten_set_main_loop(update, 0, 1);
    return 0;
}
