#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "antvm.h"
#include "stretchy_buffer.h"

int main(int argc, char *argv[]) {

	ant_word program[] = {
		0x41, 0x4e, 0x54, /* ant header */

		0x00, 0x16, /* address of pointer to function main */
		
		/* "Hello, World!\n" */
		0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a, 0x00,
		0x00, 0x1e, 		/* address of function greet */
		0x00, 0x18, 		/* address of function main */
		
		/* fn main: */
		0x0c, 0x00, 0x14,	/* call greet */
		0x01, 0x00,	0x0d,	/* exit with status code 0x00 */
		
		/* fn greet: */
		0x03, 0x00, 0x05,	/* load string at 0x0005 */
		0x11, 0x00, 0x29,	/* while (string[i] != '\0') { */
		0x30,				/*   putchar(string[i]); */
		0x04,				/*   i++; */
		0x10, 0x00, 0x21,	/* } */
		0x0a, 0x00			/* return; */
		/* fn greet end */
	};

	antvm_t vm = antvm_new(program);

	ant_address fn_main = antvm_fetchword(&vm);
	vm.registers[PC] = antvm_dereference(&vm, fn_main);

	ant_word op;
	while ((op = antvm_fetch(&vm)) != HLT) {
		//printf("Evaluating: 0x%.2x\n", op);

		switch (op) {
			case CALL: {
				ant_address fn = antvm_fetchword(&vm);
				antvm_callfn(&vm, fn);
				break;
			}
			case RET: {
				antvm_returnfn(&vm, antvm_fetch(&vm));
				break;
			}
			case PSH: {
				antvm_push(&vm, antvm_fetch(&vm));
				break;
			}
			case POP: {
				antvm_pop(&vm);
				break;
			}
			case LDS: {
				const ant_address addr = antvm_fetchword(&vm);
				ant_address i = 0;
				ant_byte val;

				stack_t strstack = stack_new(32);
				while ((val = vm.program[addr + i++]) != '\0') {
					stack_push(&strstack, val);
				}

				antvm_push(&vm, 0);
				while (!stack_empty(&strstack)) {
					antvm_push(&vm, stack_pop(&strstack));
				}

				stack_delete(&strstack);
				break;
			}
			case JMP: {
				vm.registers[PC] = antvm_fetchword(&vm);
				break;
			}
			case JEZ: {
				const ant_address addr = antvm_fetchword(&vm);
				if (antvm_top(&vm) == 0x00) {
					vm.registers[PC] = addr;
				}

				break;
			}
			case PUTC: {
				putchar(antvm_top(&vm));
				break;
			}
		};
	}

	antvm_delete(&vm);

	return 0;
}