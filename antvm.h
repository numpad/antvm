#ifndef ANTVM_H
#define ANTVM_H

#include <stdlib.h>
#include <stdint.h>
#include "stack.h"

/* How to store program instructions */
typedef unsigned char ant_byte;
typedef unsigned short ant_word;
typedef unsigned short ant_address;

enum {
	PC,
	RAX, RBX, RCX, RDX,
	REX, RFX, UNUSED,

	REGISTERS_COUNT
} ant_register;

enum {
	NOP = 0x00,
	PSH = 0x01,
	LDM = 0x02,
	LDS = 0x03,
	POP = 0x04,
	RET = 0x0a,
	CALL = 0x0c,
	HLT = 0x0d,
	JMP = 0x10,
	JEZ = 0x11,
	PUTC = 0x30
} ant_opcode;

typedef struct {
	stack_t stack,
	        function_stack;
	
	ant_word *program;
	ant_word registers[8];
} antvm_t;

/* initialize a new antvm */
antvm_t antvm_new(ant_word *program);
/* delete antvm */
void antvm_delete(antvm_t *vm);

/* fetch next program byte */
ant_word antvm_fetch(antvm_t *vm);
ant_address antvm_fetchword(antvm_t *vm);

ant_word antvm_dereference(antvm_t *vm, ant_address addr);

/* call & return from function */
void antvm_callfn(antvm_t *vm, ant_address fn);
void antvm_returnfn(antvm_t *vm, ant_byte values);

void antvm_push(antvm_t *vm, ant_byte value);
ant_byte antvm_pop(antvm_t *vm);
ant_byte antvm_top(antvm_t *vm);

#endif
