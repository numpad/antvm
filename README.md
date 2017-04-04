# ant vm


### Instruction set

| mnemonic | opcode | parameter | description |
|----------|-------:|-----------|-------------|
| NOP      |  0x00  |           | do nothing  |
| PSH      |  0x01  | <byte>    | load absolute value |
| LDM      |  0x02  | <word>    | load word at address |
| LDS      |  0x03  | <word>    | load bytes until encountering '\0' (included) |
| POP      |  0x04  |           | pop |
| RET      |  0x0a  | <byte>    | return from function, parameter is number of return values |
| CALL     |  0x0c  | <word>    | call function at <addr> |
| HLT      |  0x0d  |           | stops execution, returns value on top of stack |
| JMP      |  0x10  | <word>    | jump to address |
| JEZ      |  0x11  | <word>    | jump to address if stack top is 0 |
| PUTC     |  0x30  |           | print accumulator value as ascii |
