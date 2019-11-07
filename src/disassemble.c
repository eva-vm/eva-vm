#include <evavm/disassemble.h>
#include <evavm/eva.h>

void disassemble(opcode_t *op) { disassemble_file(stdout, op); }

void disassemble_file(FILE *f, opcode_t *op) {
	char buffer[100];
	disassemble_str(buffer, op);
	fprintf(f, "%.100s\n", buffer);
}

void disassemble_str(char *out, opcode_t *op) {
	switch (op->instruction) {
	case 0x0: {
		/* ADD,ADC, MOV between registers */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		if (op->reset)
			sprintf(out, "MOV\tR%d, R%d", op1, op2);
		else if (op->flag)
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
		if (op->reset)
			sprintf(out, "MOV\tR%d, #0x%04X", op1, op2);
		else if (op->flag)
			sprintf(out, "ADC\tR%d, #0x%04X", op1, op2);
		else
			sprintf(out, "ADD\tR%d, #0x%04X", op1, op2);
		break;
	}
	case 0x2: {
		/* PUSH or POP a register */
		uint8_t op1 = op->operands >> 16;
		if (op->flag)
			sprintf(out, "POP\tR%d", op1);
		else
			sprintf(out, "PUSH\tR%d", op1);
		break;
	}
	case 0x3: {
		/* Subtract between registers */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		if (op->flag)
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
		op1 = (op->operands & 0xF0000) >> 16;
		op2 = (op->operands & 0x0FFFF);
		sprintf(out, "LDR\tR%d, #0x%04X", op1, op2);
		break;
	}
	case 0x7: {
		/* Subtract value from register */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		if (op->flag)
			sprintf(out, "SUBC\tR%d, #0x%04X", op1, op2);
		else
			sprintf(out, "SUB\tR%d, #0x%04X", op1, op2);
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
		sprintf(out, "STR\tR%d, #0x%04X", op1, op2);
		break;
	}
	case 0xB: {
		/* Conditional branching */
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (op->offset == 0) {
			if (op->flag)
				sprintf(out, "BNEQ\tR%d", reg);
			else
				sprintf(out, "BEQ\tR%d", reg);

		} else {
			if (op->flag)
				sprintf(out, "BLT\tR%d", reg);
			else
				sprintf(out, "BLE\tR%d", reg);
		}
	}
	case 0xC: {
		/* Register value comparison */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		sprintf(out, "CMP\tR%d, R%d", op1, op2);
		break;
	}
	case 0xF: {
		/* I/O operations */
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (op->flag)
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
