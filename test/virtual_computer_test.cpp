#include <catch2/catch_test_macros.hpp>

#include "virtual_computer.h"
#include "instruction.h"

using namespace std;

TEST_CASE("Arithmetic")
{
    VirtualComputer cpu("add 45 5 ra\nadd 10 rb rb\nsub ra rb rc\nmul ra rc rd\ndiv rd rb re");
    cpu.run();
    REQUIRE(cpu.readRegister(0) == 50);
    REQUIRE(cpu.readRegister(1) == 10);
    REQUIRE(cpu.readRegister(2) == 40);
    REQUIRE(cpu.readRegister(3) == 2000);
    REQUIRE(cpu.readRegister(4) == 200);
}

TEST_CASE("Memory")
{
    VirtualComputer cpu("add 0 8 ra\nadd ra 5 [ra]\nsub [ra] 10 [8]\nadd [ra] [8] rb");
    cpu.run();
    REQUIRE(cpu.readRegister(0) == 8);
    REQUIRE(cpu.readRegister(1) == 6);
    REQUIRE(cpu.readMemory(8) == 3);
}

TEST_CASE("Jump")
{
    VirtualComputer cpu("add 5 0 ra\nadd 3 0 rb\njne ra rb ra\nadd 7 rc rc\nadd 9 rc rc\nadd ra rb [rc]");
    cpu.run();
    REQUIRE(cpu.readRegister(0) == 5);
    REQUIRE(cpu.readRegister(1) == 3);
    REQUIRE(cpu.readMemory(0) == 8);
}
