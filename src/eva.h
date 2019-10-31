#ifndef _H_EVA
#define _H_EVA
#include <stddef.h>
#include <stdint.h>

typedef struct opcode_s {
	unsigned instruction : 4;
	unsigned reset : 1;
	unsigned flag : 1;
	unsigned offset : 2;
	unsigned operands : 20;
} opcode_t;

typedef uint32_t registers_t[16];

void opcode_get_register_register(opcode_t *op, uint8_t *reg1, uint8_t *reg2);
void opcode_get_register_value(opcode_t *op, uint8_t *reg, uint16_t *val);

#endif
