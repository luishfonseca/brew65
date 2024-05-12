#include <brew65emu/tools/disassembler.h>

#include <sstream>
#include <iomanip>

extern "C"
{
#include <opctable.h>
#include <opcdesc.h>
#include <handler.h>
}

#define hex(n) std::uppercase << std::setfill('0') << std::setw(n) << std::hex
#define mnemo std::setw(8) << std::left << desc->Mnemo

using namespace brew65emu::tools;

std::string Disassembler::disassemble_opcode(uint16_t addr, uint16_t &next)
{
    std::stringstream ss;

    uint16_t pc = addr;
    uint8_t opcode = this->read(pc);

    const OpcDesc *desc = &OpcTable[opcode];

    next = pc + desc->Size;

    if (desc->Handler == OH_Illegal)
    {
        ss << "Illegal opcode";
    }
    else if (desc->Handler == OH_Accumulator)
    {
        ss << mnemo << "a";
    }
    else if (desc->Handler == OH_Implicit | desc->Handler == OH_Rts)
    {
        ss << mnemo;
    }
    else if (desc->Handler == OH_Immediate)
    {
        ss << mnemo << "#$" << hex(2) << (int)this->read(pc + 1);
    }
    else if (desc->Handler == OH_Direct)
    {
        ss << mnemo << "$" << hex(2) << (int)this->read(pc + 1);
    }
    else if (desc->Handler == OH_DirectX)
    {
        ss << mnemo << "$" << hex(2) << (int)this->read(pc + 1) << ",x";
    }
    else if (desc->Handler == OH_DirectY)
    {
        ss << mnemo << "$" << hex(2) << (int)this->read(pc + 1) << ",y";
    }
    else if (desc->Handler == OH_Absolute || desc->Handler == OH_JmpAbsolute || desc->Handler == OH_JsrAbsolute)
    {
        ss << mnemo;

        if (desc->Flags & flFarOverride)
        {
            ss << "f:";
        }
        else if ((desc->Flags & flAbsOverride) && pc < 0x100)
        {
            ss << "a:";
        }

        ss << "$" << hex(4) << (this->read(pc + 1) | (this->read(pc + 2) << 8));
    }
    else if (desc->Handler == OH_AbsoluteX)
    {
        ss << mnemo;

        if (desc->Flags & flFarOverride)
        {
            ss << "f:";
        }
        else if ((desc->Flags & flAbsOverride) && pc < 0x100)
        {
            ss << "a:";
        }

        ss << "$" << hex(4) << (this->read(pc + 1) | (this->read(pc + 2) << 8)) << ",x";
    }
    else if (desc->Handler == OH_DirectX)
    {
        ss << mnemo << "$" << hex(2) << (int)this->read(pc + 1) << ",x";
    }
    else if (desc->Handler == OH_DirectY)
    {
        ss << mnemo << "$" << hex(2) << (int)this->read(pc + 1) << ",y";
    }
    else if (desc->Handler == OH_Relative)
    {
        ss << mnemo << "* + (" << hex(4) << (this->read(pc + 1) + 2) << ")";
    }
    else if (desc->Handler == OH_DirectIndirectY)
    {
        ss << mnemo << "($" << hex(2) << (int)this->read(pc + 1) << "),y";
    }
    else if (desc->Handler == OH_DirectXIndirect)
    {
        ss << mnemo << "($" << hex(2) << (int)this->read(pc + 1) << ",x)";
    }
    else if (desc->Handler == OH_JmpAbsoluteIndirect)
    {
        ss << mnemo << "($" << hex(4) << (this->read(pc + 1) | (this->read(pc + 2) << 8)) << ")";
    }
    else
    {
        ss << "Unknown handler";
        next = pc + 1;
    }

    ss << "\t; " << hex(4) << pc;
    for (int i = 0; i < desc->Size; i++)
    {
        ss << " " << hex(2) << (int)this->read(pc + i);
    }

    if (desc->Handler == OH_Rts || desc->Handler == OH_JmpAbsolute || desc->Handler == OH_JmpAbsoluteIndirect)
    {
        ss << std::endl
           << "\t\t; ----------------";
    }

    return ss.str();
}
