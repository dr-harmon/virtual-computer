#include "assembler.h"

#include <sstream>

using namespace std;

void Assembler::parse(const string& program, std::vector<std::unique_ptr<Instruction>>& instructions)
{
    auto programStream = istringstream{program};
    string line;
    while (getline(programStream, line, '\n')) {
        auto lineStream = istringstream(line);
        string instruction, param1, param2, param3;
        lineStream >> instruction;
        lineStream >> param1;
        lineStream >> param2;
        lineStream >> param3;
        instructions.push_back(Instruction::parse(instruction, param1, param2, param3));
    }
}
