#include <evavm/eva.h>
#include "log.h"

#if DENABLED(DLVL_DEBUG)
#include <evavm/disassemble.h>
#endif

void eval_mov_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);
	registers[r1] = registers[r2];
}

void eval_mov_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t val;
	opcode_get_register_value(op, &r, &val);
	registers[r] = val;
}

void eval_add_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);
	registers[r1] += registers[r2];
}

void eval_add_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t val;
	opcode_get_register_value(op, &r, &val);
	registers[r] += val;
}

void eval_addc_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);

	if (((registers[r1] > 0) && (registers[r2] > INT_MAX - registers[r1])) ||
	    ((registers[r1] < 0) && (registers[r2] < INT_MAX - registers[r1]))) {
		registers[EVA_REG_FLAG] = 1;
	}

	registers[r1] += registers[r2];
}

void eval_addc_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t val;
	opcode_get_register_value(op, &r, &val);

	if (((registers[r] > 0) && (val > INT_MAX - registers[r])) ||
	    ((registers[r] < 0) && (val < INT_MAX - registers[r]))) {
		registers[EVA_REG_FLAG] = 1;
	}

	registers[r] += val;
}

void eval_sub_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);

	registers[r1] -= registers[r2];
}

void eval_sub_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t val;
	opcode_get_register_value(op, &r, &val);

	registers[r] -= val;
}

void eval_subc_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);

	if (((registers[r1] < 0) && (registers[r2] > INT_MAX - registers[r1])) ||
	    ((registers[r1] > 0) && (registers[r2] < INT_MIN - registers[r1]))) {
		registers[EVA_REG_FLAG] = 1;
	}

	registers[r1] -= registers[r2];
}
void eval_subc_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t val;
	opcode_get_register_value(op, &r, &val);

	if (((registers[r] < 0) && (val > INT_MAX - registers[r])) ||
	    ((registers[r] > 0) && (val < INT_MIN - registers[r]))) {
		registers[EVA_REG_FLAG] = 1;
	}

	registers[r] -= val;
}

void eval_ldr_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);
	registers[r1] = OPCODE2INT(ram[registers[r2]]);
}
void eval_ldr_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t adr;
	opcode_get_register_value(op, &r, &adr);

	registers[r] = OPCODE2INT(ram[adr]);
}

void eval_str_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);

	ram[registers[r2]] = registers[r1];
}
void eval_str_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	uint16_t adr;
	opcode_get_register_value(op, &r, &adr);

	ram[adr] = registers[r];
}

// TODO
void eval_push_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	LOG_ERROR("PUSH is not supported at the moment");
}
// TODO
void eval_pop_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	LOG_ERROR("POP is not supported at the moment");
}

void eval_in_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t reg;
	opcode_get_register_register(op, &reg, NULL);
	registers[reg] = getchar();
}
void eval_out_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t reg;
	opcode_get_register_register(op, &reg, NULL);
	putchar(registers[reg]);
}

void eval_beq_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	opcode_get_register_register(op, &r, NULL);
	if (registers[EVA_REG_CMP] == EVA_CMP_EQUALS)
		registers[EVA_REG_PC] = registers[r]-1; // PC will get re-incremented at the next iteration
}
void eval_bneq_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	opcode_get_register_register(op, &r, NULL);
	if (registers[EVA_REG_CMP] != EVA_CMP_EQUALS)
		registers[EVA_REG_PC] = registers[r]-1; // PC will get re-incremented at the next iteration
}
void eval_blt_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	opcode_get_register_register(op, &r, NULL);
	if (registers[EVA_REG_CMP] == EVA_CMP_LESS_THAN)
		registers[EVA_REG_PC] = registers[r]-1; // PC will get re-incremented at the next iteration
}
void eval_ble_r(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r;
	opcode_get_register_register(op, &r, NULL);
	if (registers[EVA_REG_CMP] != EVA_CMP_GREATER_THAN)
		registers[EVA_REG_PC] = registers[r]-1; // PC will get re-incremented at the next iteration
}

void eval_cmp_rr(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t r1, r2;
	opcode_get_register_register(op, &r1, &r2);
	int32_t val1 = registers[r1], val2 = registers[r2];
	eva_comp_t cmp;
	if (val1 == val2)
		cmp = EVA_CMP_EQUALS;
	else if (val1 < val2)
		cmp = EVA_CMP_LESS_THAN;
	else
		cmp = EVA_CMP_GREATER_THAN;
	registers[EVA_REG_CMP] = (int32_t)cmp;
}

void eval_cmp_rc(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t reg;
	uint16_t val;
	opcode_get_register_value(op, &reg, &val);
	eva_comp_t cmp;
	if (registers[reg] == val)
		cmp = EVA_CMP_EQUALS;
	else if (registers[reg] < val)
		cmp = EVA_CMP_LESS_THAN;
	else
		cmp = EVA_CMP_GREATER_THAN;
	registers[EVA_REG_CMP] = (int32_t)cmp;
}

void opcode_eval(uint32_t *op, uint32_t *ram, registers_t registers) {
	uint8_t code, offset;
	bool reset, flag;
#if DENABLED(DLVL_DEBUG)
	char _out[100] = {0};
	disassemble_str(_out, op);
	LOG_DEBUG("[pc %d] opcode: %.100s", registers[EVA_REG_PC], _out);
#endif
	opcode_get_data(op, &code, &reset, &flag, &offset);
	switch (code) {
	case 0x0:
		if (reset)
			eval_mov_rr(op, ram, registers);
		else if (flag)
			eval_addc_rr(op, ram, registers);
		else
			eval_add_rr(op, ram, registers);
		break;
	case 0x1:
		if (reset)
			eval_mov_rc(op, ram, registers);
		else if (flag)
			eval_addc_rc(op, ram, registers);
		else
			eval_add_rc(op, ram, registers);
		break;
	case 0x2:
		if (flag)
			eval_pop_r(op, ram, registers);
		else
			eval_push_r(op, ram, registers);
		break;
	case 0x3:
		if (flag)
			eval_subc_rr(op, ram, registers);
		else
			eval_sub_rr(op, ram, registers);
		break;
	case 0x4:
		eval_ldr_rr(op, ram, registers);
		break;
	case 0x5:
		eval_ldr_rc(op, ram, registers);
		break;
	case 0x7:
		if (flag)
			eval_subc_rc(op, ram, registers);
		else
			eval_sub_rc(op, ram, registers);
		break;
	case 0x8:
		eval_str_rr(op, ram, registers);
		break;
	case 0x9:
		eval_str_rc(op, ram, registers);
		break;
	case 0xB:
		if (offset == 0) {
			if (flag)
				eval_bneq_r(op, ram, registers);
			else
				eval_beq_r(op, ram, registers);
		} else {
			if (flag)
				eval_blt_r(op, ram, registers);
			else
				eval_ble_r(op, ram, registers);
		}
		break;
	case 0xC: {
		if(offset == 0)
			eval_cmp_rr(op, ram, registers);
		else
			eval_cmp_rc(op, ram, registers);
		break;
	}
	case 0xF:
		if (flag)
			eval_out_r(op, ram, registers);
		else
			eval_in_r(op, ram, registers);
		break;
	default:
		fprintf(stderr, "Unknown instruction %X\n", code);
		break;
	}
	LOG_DEBUG("        R0: %d, R1: %d", registers[0], registers[1]);
}
