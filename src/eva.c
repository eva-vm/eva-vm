#include "eva.h"

void opcode_get_register_register(opcode_t *op, uint8_t *reg1, uint8_t *reg2) {
	if (reg1)
		*reg1 = (op->operands & 0xF0000) >> 16;
	if (reg2)
		*reg2 = (op->operands & 0x0F000) >> 12;
}

void opcode_get_register_value(opcode_t *op, uint8_t *reg, uint16_t *val) {
	if (reg)
		*reg = (op->operands & 0xF0000) >> 16;
	if (val)
		*val = op->operands & 0x0FFFF;
}
