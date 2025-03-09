#pragma once

#include <memory>
#include <string>
#include <vector>

#include "instruction.h"

class Assembler {
public:
    static void parse(const std::string& program, std::vector<std::unique_ptr<Instruction>>& instructions);
};
