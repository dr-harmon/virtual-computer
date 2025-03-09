#pragma once

#include <memory>
#include <string>
#include <vector>

class Instruction;

class VirtualComputer {
    std::vector<int> registers;
    std::vector<int> memory;
    std::vector<std::unique_ptr<Instruction>> instructions;
    int programCounter = 0;
public:
    VirtualComputer(const std::string& program);
    void run();
    int readRegister(int registerIndex) const;
    void writeRegister(int registerIndex, int value);
    int readMemory(int memoryOffset) const;
    void writeMemory(int memoryOffset, int value);
    void jump(int instructionOffset);
};
