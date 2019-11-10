#ifndef _H_EVA
#define _H_EVA
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Type alias for the 16 registers that the programs will use
 *
 */
typedef int32_t registers_t[16];

/**
 * @brief Enum as used by the CMP instruction, to hold comparison results.
 *
 */
typedef enum {
	EVA_CMP_UNSET,
	EVA_CMP_EQUALS,
	EVA_CMP_LESS_THAN,
	EVA_CMP_GREATER_THAN
} eva_comp_t;

/** @brief Flag register index */
#define EVA_REG_FLAG 11
/** @brief Frame pointer register index */
#define EVA_REG_FP 12
/** @brief Stack pointer register index */
#define EVA_REG_SP 13
/** @brief Comparison results register index */
#define EVA_REG_CMP 14
/** @brief Program counter register index */
#define EVA_REG_PC 15

/**
 * @brief Read an op-code from the input file in.
 *
 * @param out Output adress that will contain the read op-code.
 * @param in Input file object. Must be opened in binary read mode.
 * @return size_t number of bytes read (as returned by the underlying fread)
 */
size_t opcode_read(uint32_t *out, FILE *in);
/**
 * @brief Extracts the instruction from an op-code
 *
 * @param op Op-code to read from
 * @param code 4-bit instruction code
 * @param reset Reset flag
 * @param flag Flag flag
 * @param offset Offset amount
 */
void opcode_get_data(uint32_t *op, uint8_t *code, bool *reset, bool *flag,
                     uint8_t *offset);
/**
 * @brief Extract the register operands from the input op-code.
 *
 * @param op Input op-code
 * @param reg1 Output variable to register 1
 * @param reg2 Output variable to register 2
 */
void opcode_get_register_register(uint32_t *op, uint8_t *reg1, uint8_t *reg2);
/**
 * @brief Extrace the register and constant value operands from the input
 * op-code.
 *
 * @param op Input op-code
 * @param reg Output variable to register
 * @param val Output variable to constant value
 */
void opcode_get_register_value(uint32_t *op, uint8_t *reg, uint16_t *val);

/**
 * @brief Evaluates an op-code.
 *
 * @param op Op-code to evaluate
 * @param ram RAM array
 * @param registers Registers array
 */
void opcode_eval(uint32_t *op, uint32_t *ram, registers_t registers);

#endif
