# Virtual Computer

In this lab, you will build a virtual computer that executes the instructions of a simple assembly language. The computer has the following characteristics:

* It contains a set of registers (like variables) that store integers and can be used to move and process data via instructions.
* Instructions execute sequentially.
* Instructions support constant values for arguments in addition to registers.

Here are some example instructions:

```
add 45 5 ra   # add 45 + 5, store result in ra
add 10 rb rb  # add 10 to rb, store in rb
sub ra rb rc  # subtract ra (50) - rb (10), store the result (40) in rc
```

The assembler should take a newline-separated string of assembly language code and parse it into instructions. These instructions should then be fed into the virtual computer, which executes them.

Implement whatever sort of abstractions make the most sense to you, but try to design for extensibility. For this entire exercise, you can assume that the given input will always be correctly formatted.

## Part 1: Arithmetic instructions with 2 operand modes

As a first step, implement basic arithmetic functionality for the language, including the add and subtract instructions mentioned in the earlier example as well as instructions for multiplication and division.

```
add 45 5 ra
add 10 rb rb
sub ra rb rc
mul ra rc rd
div rd rb re
```

Registers that are not initialized should be treated as 0. Therefore, the final register state should be:

```
ra = 50, rb = 10, rc = 40, rd = 2000, re = 200
```

Your first test should take in a single string that contains multiple instruction statements separated by newline characters:

```
add 45 5 ra\nadd 10 rb rb\nsub ra rb rc\nmul ra rc rd\ndiv rd rb re
```

## Part 2: Memory and additional operand types

Now that we have a couple working instructions, it's time to implement memory. Most processors have a small, finite amount of pre-defined registers, so they need a larger but slower store for larger sets of data. With that in mind, memory should be some indexable data structure, where each offset is capable of storing the full contents of a register. For example, we might want to set memory[55] = 10. To interact with memory, we will need to add two new instruction operand types to our language:

```
add 0 8 ra       # store 8 into ra
add ra 5 [ra]    # add 5 to ra (8), store result in memory[ra] (ra is still 8, so mem[8] = 13);
                 # memory[ra] = ra + 5
sub [ra] 10 [8]  # load memory[ra] and subtract 10 from it, store the result back into memory[8];
                 # memory[8] = memory[ra] - 10
add [ra] [8] rb  # should result in rb = 3 + 3
```

The final register state should show ra = 8, rb = 6, and memory should show memory[8] = 3. We will use this new example as our new test string:

```
add 0 8 ra\nadd ra 5 [ra]\nsub [ra] 10 [8]\nadd [ra] [8] rb
```

## Part 3: Conditional branching

To finally reach Turing completeness, we need to support conditional operations. The simplest way to do this is to implement conditional branches. For example:

```
0: add 5 0 ra      # ra = 5
1: add 3 0 rb      # rb = 3
2: jne ra rb ra    # jump to ra (third parameter) if ra (first parameter) != rb (second parameter)
3: add 7 rc rc     # should be skipped
4: add 9 rc rc     # should be skipped
5: add ra rb [rc]  # jump should land here
```

Line numbers are included to illustrate how the jump destination should be interpreted.

`jne` stands for "jump if not equal". The final parameter is a global offset from the start of the program. (Line numbers start at 0.)

Raw input:

```
add 5 0 ra\nadd 3 0 rb\njne ra rb ra\nadd 7 rc rc\nadd 9 rc rc\nadd ra rb [rc]
```

The final output should show ra = 5, rb = 3, and memory[0] = 8

## Hints

* Applying good OOP principles in the first part will save trouble in the subsequent parts. In particular, having distinct classes for the virtual computer and for the assembled instructions is good design and will really help out later. For example, you might encapsulate the virtual computer in a class and the instructions in a separate class. The instruction class will also benefit from inheritance, though that will require some foresight. Don't copy-paste too much code between add/subtract/multiply/divide. Find a way to reduce the amount of repetition.
* All registers should be initialized to zero. (This can be inferred from the test cases.)
* You can manually pre-define each available register, or you dynamically create new registers in a data structure of choice as they’re encountered.
* You can assume all registers start with a lower-case "r".
* To test your implementation, you will need some way to print out the register state at the end of the program.
* Do not attempt floating point operations. The virtual computer only supports integer arithmetic.
* You can assume there will be the valid number of operands for a given operator.
* Don't forget to support instructions like `sub [ra] 10 [8]` which has a constant value as the final parameter.
* To implement memory, it helps to implement a "read" primitive and a "write" primitive, where the read primitive will resolve one of the two input parameters into an integer value, and the write primitive will store an integer value into whatever the output parameter is pointing at. An elegant solution here involves abstracting away the parameters themselves such that the individual instruction implementations can just say `destination_operand.write_value(source_operand_1.read())` and the object will handle interacting with the engine appropriately.
