#pragma once

#include <memory>
#include <string>
#include <vector>

#include "virtual_computer.h"
#include "operand.h"

class Instruction {
protected:
    std::unique_ptr<Operand> operand1;
    std::unique_ptr<Operand> operand2;
    std::unique_ptr<Operand> operandOut;
public:
    static std::unique_ptr<Instruction> parse(const std::string& instruction, const std::string& param1, const std::string& param2, const std::string& param3);
    Instruction(const std::string& op1, const std::string& op2, const std::string& opOut);
    virtual void execute(VirtualComputer& cpu);
};

class AddInstruction : public Instruction {
public:
    using Instruction::Instruction;
    virtual void execute(VirtualComputer& cpu);
};

class SubtractInstruction : public Instruction {
public:
    using Instruction::Instruction;
    virtual void execute(VirtualComputer& cpu);
};

class MultiplyInstruction : public Instruction {
public:
    using Instruction::Instruction;
    virtual void execute(VirtualComputer& cpu);
};

class DivideInstruction : public Instruction {
public:
    using Instruction::Instruction;
    virtual void execute(VirtualComputer& cpu);
};

class JumpInstruction : public Instruction {
public:
    using Instruction::Instruction;
    virtual void execute(VirtualComputer& cpu);
};
