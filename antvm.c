#include "antvm.h"

/* initialize a new antvm */
antvm_t antvm_new(ant_word *program) {
	antvm_t vm;

	/* allocate stack space  */
	vm.stack = stack_new(128);
	vm.function_stack = stack_new(32);

	/* set registers to 0 */
	for (size_t i = 0; i < REGISTERS_COUNT; ++i) {
		vm.registers[i] = 0;
	}
	vm.registers[PC] = 3;


	vm.program = program;
	
	return vm;
}

/* free memory */
void antvm_delete(antvm_t *vm) {
	stack_delete(&vm->stack);
	stack_delete(&vm->function_stack);
}

ant_word antvm_fetch(antvm_t *vm) {
	return vm->program[vm->registers[PC]++];
}

ant_address antvm_fetchword(antvm_t *vm) {
	return antvm_fetch(vm) << 8 | antvm_fetch(vm);
}

ant_address antvm_dereference(antvm_t *vm, ant_address addr) {
	return vm->program[addr] << 8 | vm->program[addr + 1];
}

void antvm_callfn(antvm_t *vm, ant_address fn) {
	stack_push(&(vm->function_stack), vm->registers[PC]);
	vm->registers[PC] = antvm_dereference(vm, fn);
}

void antvm_returnfn(antvm_t *vm, ant_byte values) {
	vm->registers[PC] = stack_pop(&(vm->function_stack));
}

void antvm_push(antvm_t *vm, ant_byte value) {
	stack_push(&vm->stack, value);
}

ant_byte antvm_pop(antvm_t *vm) {
	return stack_pop(&vm->stack);
}

ant_byte antvm_top(antvm_t *vm) {
	return stack_top(&vm->stack);
}