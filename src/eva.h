#ifndef _H_EVA
#define _H_EVA
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct opcode_s {
	unsigned instruction : 4;
	unsigned reset : 1;
	unsigned flag : 1;
	unsigned offset : 2;
	unsigned operands : 20;
} opcode_t;

typedef int32_t registers_t[16];

#define EVA_REG_FLAG 11
#define EVA_REG_PC 15

size_t opcode_read(opcode_t *out, FILE *in);
void opcode_get_register_register(opcode_t *op, uint8_t *reg1, uint8_t *reg2);
void opcode_get_register_value(opcode_t *op, uint8_t *reg, uint16_t *val);

void opcode_eval(opcode_t *op, opcode_t *ram, registers_t registers);

#endif
