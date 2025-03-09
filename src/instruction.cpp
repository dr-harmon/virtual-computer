#include "instruction.h"
#include "operand.h"

#include <stdexcept>

using namespace std;

unique_ptr<Instruction> Instruction::parse(const string& instruction, const string& param1, const string& param2, const string& param3)
{
    if (instruction == "add") {
        return make_unique<AddInstruction>(param1, param2, param3);
    } else if (instruction == "sub") {
        return make_unique<SubtractInstruction>(param1, param2, param3);
    } else if (instruction == "mul") {
        return make_unique<MultiplyInstruction>(param1, param2, param3);
    } else if (instruction == "div") {
        return make_unique<DivideInstruction>(param1, param2, param3);
    } else if (instruction == "jne") {
        return make_unique<JumpInstruction>(param1, param2, param3);
    } else {
        throw runtime_error("Unknown instruction " + instruction);
    }
}

Instruction::Instruction(const string& op1, const string& op2, const string& opOut) :
    operand1(Operand::parse(op1)), operand2(Operand::parse(op2)), operandOut(Operand::parse(opOut))
{
}

void Instruction::execute(VirtualComputer& cpu)
{
    throw runtime_error("Cannot execute an abstract instruction");
}

void AddInstruction::execute(VirtualComputer& cpu)
{
    operandOut->write(cpu, ImmediateOperand(operand1->read(cpu) + operand2->read(cpu)));
}

void SubtractInstruction::execute(VirtualComputer& cpu)
{
    operandOut->write(cpu, ImmediateOperand(operand1->read(cpu) - operand2->read(cpu)));
}

void MultiplyInstruction::execute(VirtualComputer& cpu)
{
    operandOut->write(cpu, ImmediateOperand(operand1->read(cpu) * operand2->read(cpu)));
}

void DivideInstruction::execute(VirtualComputer& cpu)
{
    operandOut->write(cpu, ImmediateOperand(operand1->read(cpu) / operand2->read(cpu)));    
}

void JumpInstruction::execute(VirtualComputer& cpu)
{
    if (operand1->read(cpu) != operand2->read(cpu)) {
        cpu.jump(operandOut->read(cpu));
    }
}
