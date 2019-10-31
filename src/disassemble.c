#include "disassemble.h"
#include "eva.h"
#include <stdint.h>
#include <stdio.h>

void disassemble(opcode_t *op) {
	switch (op->instruction) {
	case 0x0: {
		/* ADD,ADC, MOV between registers */
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		if (op->reset)
			printf("MOV\tR%d, R%d\n", op1, op2);
		else if (op->flag)
			printf("ADC\tR%d, R%d\n", op1, op2);
		else
			printf("ADD\tR%d, R%d\n", op1, op2);
		break;
	}
	case 0x1: {
		/* ADD, ADC, MOV with a register and a value */
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		if (op->reset)
			printf("MOV\tR%d, #%04X\n", op1, op2);
		else if (op->flag)
			printf("ADC\tR%d, #%04X\n", op1, op2);
		else
			printf("ADD\tR%d, #%04X\n", op1, op2);
		break;
	}
	case 0x2: {
		/* PUSH or POP a register */
		uint8_t op1 = op->operands >> 16;
		if (op->flag)
			printf("POP\tR%d\n", op1);
		else
			printf("PUSH\tR%d\n", op1);
		break;
	}
	case 0x4: {
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		printf("LDR\tR%d", op1);
		if (op2)
			printf(", R%d\n", op2);
		else
			printf("\n");
		break;
	}
	case 0x5: {
		uint8_t op1;
		uint16_t op2;
		op1 = (op->operands & 0xF0000) >> 16;
		op2 = (op->operands & 0x0FFFF);
		printf("LDR\tR%d, %04X\n", op1, op2);
		break;
	}
	case 0x8: {
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		printf("STR\tR%d", op1);
		if (op2)
			printf(", R%d", op2);
		printf("\n");
		break;
	}
	case 0x9: {
		uint8_t op1;
		uint16_t op2;
		opcode_get_register_value(op, &op1, &op2);
		printf("STR\tR%d, %04X\n", op1, op2);
		break;
	}
	case 0xB: {
		uint8_t reg;
		opcode_get_register_register(op, &reg, NULL);
		if (op->offset == 0) {
			if (op->flag)
				printf("BNEQ\tR%d", reg);
			else
				printf("BEQ\tR%d", reg);

		} else {
			if (op->flag)
				printf("BLT\tR%d", reg);
			else
				printf("BLE\tR%d", reg);
		}
		printf("\n");
	}
	case 0xC: {
		uint8_t op1, op2;
		opcode_get_register_register(op, &op1, &op2);
		printf("CMP\tR%d, R%d\n", op1, op2);
		break;
	}
	default:
		printf("#### ; Unrecognized opcode\n");
		break;
	}
}
