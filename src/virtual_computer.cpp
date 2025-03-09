#include "virtual_computer.h"

#include "assembler.h"
#include "instruction.h"

using namespace std;

const int MAX_REGISTERS = 32;
const int MAX_MEMORY_WORDS = 256;

VirtualComputer::VirtualComputer(const string& program) : registers(MAX_REGISTERS, 0), memory(MAX_MEMORY_WORDS, 0)
{
    Assembler::parse(program, instructions);
}

void VirtualComputer::run()
{
    while (programCounter < instructions.size()) {
        instructions[programCounter]->execute(*this);
        programCounter++;
    }
}

int VirtualComputer::readRegister(int registerIndex) const
{
    return registers[registerIndex];
}

void VirtualComputer::writeRegister(int registerIndex, int value)
{
    registers[registerIndex] = value;
}

int VirtualComputer::readMemory(int memoryOffset) const
{
    return memory[memoryOffset];
}

void VirtualComputer::writeMemory(int memoryOffset, int value)
{
    memory[memoryOffset] = value;
}

void VirtualComputer::jump(int instructionOffset)
{
    // Jump to the instruction before the desired offset because the
    // program counter increments after the instruction executes
    programCounter = instructionOffset - 1;
}
