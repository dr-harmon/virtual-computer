#pragma once

#include <string>
#include <vector>

class VirtualComputer {
    std::vector<int> registers;
    std::vector<int> memory;
public:
    VirtualComputer(const std::string& program);
    void run();
    int readRegister(int registerIndex) const;
    void writeRegister(int registerIndex, int value);
    int readMemory(int memoryOffset) const;
    void writeMemory(int memoryOffset, int value);
};
