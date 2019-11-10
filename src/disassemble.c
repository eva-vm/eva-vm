#include <evavm/disassemble.h>
#include <evavm/eva.h>

void disassemble(uint32_t *op) { disassemble_file(stdout, op); }

void disassemble_file(FILE *f, uint32_t *op) {
	char buffer[100];
	disassemble_str(buffer, op);
	fprintf(f, "%.100s\n", buffer);
}

void disassemble_str(char *out, uint32_t *op) {
	uint8_t code, offset;
	bool reset, flag;
	opcode_get_data(op, &code, &reset, &flag, &offset);
	switch (code) {
	case 0x0: {
		/* ADD,ADC, MOV between registers */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		if (reset)
			sprintf(out, "MOV\tR%d, R%d", op1, op2);
		else if (flag)
			sprintf(out, "ADC\tR%d, R%d", op1, op2);
		else
			sprintf(out, "ADD\tR%d, R%d", op1, op2);
		break;
	}
	case 0x1: {
		/* ADD, ADC, MOV with a register and a value */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		if (reset)
			sprintf(out, "MOV\tR%d, #%d", op1, op2);
		else if (flag)
			sprintf(out, "ADC\tR%d, #%d", op1, op2);
		else
			sprintf(out, "ADD\tR%d, #%d", op1, op2);
		break;
	}
	case 0x2: {
		/* PUSH or POP a register */
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (flag)
			sprintf(out, "POP\tR%d", reg);
		else
			sprintf(out, "PUSH\tR%d", reg);
		break;
	}
	case 0x3: {
		/* Subtract between registers */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		if (flag)
			sprintf(out, "SUBC\tR%d, R%d", op1, op2);
		else
			sprintf(out, "SUB\tR%d, R%d", op1, op2);
		break;
	}
	case 0x4: {
		/* LDR from/to register(s) */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		sprintf(out, "LDR\tR%d, [R%d]", op1, op2);

		break;
	}
	case 0x5: {
		/* LDR value from register */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		sprintf(out, "LDR\tR%d, #%d", op1, op2);
		break;
	}
	case 0x7: {
		/* Subtract value from register */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		if (flag)
			sprintf(out, "SUBC\tR%d, #%d", op1, op2);
		else
			sprintf(out, "SUB\tR%d, #%d", op1, op2);
		break;
	}
	case 0x8: {
		/* STR from/to register(s) */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		sprintf(out, "STR\tR%d, [R%d]", op1, op2);

		break;
	}
	case 0x9: {
		/* STR value into register */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		sprintf(out, "STR\tR%d, #%d", op1, op2);
		break;
	}
	case 0xB: {
		/* Conditional branching */
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (offset == 0) {
			if (flag)
				sprintf(out, "BNEQ\tR%d", reg);
			else
				sprintf(out, "BEQ\tR%d", reg);

		} else {
			if (flag)
				sprintf(out, "BLT\tR%d", reg);
			else
				sprintf(out, "BLE\tR%d", reg);
		}
		break;
	}
	case 0xC: {
		/* Register value comparison */
		uint8_t op1;
		if (offset) {
			uint16_t val;
			opcode_get_register_value(op, &op1, &val);
			sprintf(out, "CMP\tR%d, #%d", op1, val);
		} else {
			uint8_t op2;
			opcode_get_register_register(op, &op1, &op2);
			sprintf(out, "CMP\tR%d, R%d", op1, op2);
		}
		break;
	}
	case 0xF: {
		/* I/O operations */
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (flag)
			sprintf(out, "OUT\tR%d", reg);
		else
			sprintf(out, "IN\tR%d", reg);
		break;
	}
	default:
		sprintf(out, "#### ; Unrecognized opcode");
		break;
	}
}
