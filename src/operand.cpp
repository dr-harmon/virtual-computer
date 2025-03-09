#include "operand.h"

#include <stdexcept>

using namespace std;

unique_ptr<Operand> Operand::parse(const string& opStr)
{
    if (opStr.starts_with("r")) {
        return make_unique<RegisterOperand>(opStr[1] - 'a');
    } else if (opStr.starts_with("[")) {
        auto offset = parse(opStr.substr(1, opStr.length() - 2));
        return make_unique<MemoryOperand>(std::move(offset));
    } else {
        return make_unique<ImmediateOperand>(stoi(opStr));
    }
}

int Operand::read(const VirtualComputer& cpu) const
{
    throw runtime_error("Cannot get an abstract operand");
}

void Operand::write(VirtualComputer& cpu, const Operand& value) const
{
    throw runtime_error("Cannot set an abstract operand");
}

ImmediateOperand::ImmediateOperand(int val) : value(val)
{   
}

int ImmediateOperand::read(const VirtualComputer& cpu) const
{
    return value;
}

void ImmediateOperand::write(VirtualComputer& cpu, const Operand& value) const
{
    throw runtime_error("Cannot set an immediate operand");
}

RegisterOperand::RegisterOperand(int index) : registerIndex(index)
{
}

int RegisterOperand::read(const VirtualComputer& cpu) const
{
    return cpu.readRegister(registerIndex);
}

void RegisterOperand::write(VirtualComputer& cpu, const Operand& value) const
{
    cpu.writeRegister(registerIndex, value.read(cpu));
}

MemoryOperand::MemoryOperand(unique_ptr<Operand> offset) : memoryOffset(std::move(offset))
{
}

int MemoryOperand::read(const VirtualComputer& cpu) const
{
    return cpu.readMemory(memoryOffset->read(cpu));
}

void MemoryOperand::write(VirtualComputer& cpu, const Operand& value) const
{
    cpu.writeMemory(memoryOffset->read(cpu), value.read(cpu));
}
