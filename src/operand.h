#pragma once

#include "virtual_computer.h"

#include <memory>
#include <string>
#include <vector>

class Operand {
public:
    static std::unique_ptr<Operand> parse(const std::string& opStr);
    virtual int read(const VirtualComputer& cpu) const;
    virtual void write(VirtualComputer& cpu, const Operand& value) const;
};

class ImmediateOperand : public Operand {
    int value;
public:
    ImmediateOperand(int val);
    virtual int read(const VirtualComputer& cpu) const;
    virtual void write(VirtualComputer& cpu, const Operand& value) const;
};

class RegisterOperand : public Operand {
    int registerIndex;
public:
    RegisterOperand(int index);
    virtual int read(const VirtualComputer& cpu) const;
    virtual void write(VirtualComputer& cpu, const Operand& value) const;
};

class MemoryOperand : public Operand {
    std::unique_ptr<Operand> memoryOffset;
public:
    MemoryOperand(std::unique_ptr<Operand> offset);
    virtual int read(const VirtualComputer& cpu) const;
    virtual void write(VirtualComputer& cpu, const Operand& value) const;
};
