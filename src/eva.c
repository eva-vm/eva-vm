#include <evavm/eva.h>

size_t opcode_read(uint32_t *out, FILE *in) {
	uint8_t bits[4];
	size_t size = fread(bits, sizeof(uint8_t), 4, in);
	*out = (uint32_t)(bits[0] << 24 | bits[1] << 16 | bits[2] << 8 | bits[3]);
	return size;
}

void opcode_get_data(uint32_t *op, uint8_t *code, bool *reset, bool *flag,
                     uint8_t *offset) {
	if (code)
		*code = (*op & 0xF0000000) >> 28;
	if (reset)
		*reset = (*op & 0x8000000) > 0;
	if (flag)
		*flag = (*op & 0x4000000) > 0;
	if (offset)
		*offset = (*op & 0x3000000) >> 24;
}

void opcode_get_register_register(uint32_t *op, uint8_t *reg1, uint8_t *reg2) {
	if (reg1)
		*reg1 = (*op & 0xF0000) >> 16;
	if (reg2)
		*reg2 = (*op & 0x0F000) >> 12;
}

void opcode_get_register_value(uint32_t *op, uint8_t *reg, uint16_t *val) {
	if (reg)
		*reg = (*op & 0xF0000) >> 16;
	if (val)
		*val = (*op & 0x0FFFF);
}
