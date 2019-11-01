#include "eva.h"

size_t opcode_read(opcode_t *out, FILE *in) {
	uint8_t bits[4];
	size_t size = fread(bits, sizeof(uint8_t), 4, in);
	out->instruction = (bits[0] & 0xF0) >> 4;
	out->reset = (bits[0] & 0x08) >> 3;
	out->flag = (bits[0] & 0x04) >> 2;
	out->offset = bits[0] & 0x03;
	out->operands = (bits[1] << 16) | (bits[2] << 8) | (bits[3]);
	return size;
}

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
