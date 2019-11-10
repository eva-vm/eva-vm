#ifndef _H_EVA
#define _H_EVA
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Op-code structure. Made to hold in a 32-bit integer.
 *
 *
 *
 */
typedef struct opcode_s {
	/**
	 * @brief 4-bit instruction code.
	 *
	 * The instruction code allows the Eva VM to know what the op-codes tells it
	 * to.
	 */
	unsigned instruction : 4;
	/**
	 * @brief Reset indicator.
	 *
	 * This flag is typically set when op-codes associated with a register
	 * initialization operation.
	 */
	unsigned reset : 1;
	/**
	 * @brief Flag indicator.
	 *
	 * This flag is set when op-codes will use the flag register as part of the
	 * operation.
	 *
	 */
	unsigned flag : 1;
	/**
	 * @brief Offset amount
	 *
	 * The offset amount tells the VM which nibble (4-bit word) to use in the
	 * register or memory location.
	 *
	 */
	unsigned offset : 2;
	/**
	 * @brief Operands data.
	 *
	 * As a register holds in 4 bits, it is packed at the
	 * start. The second register or constant comes after, taking another 4 bits
	 * or the remaining 16 bits, respectively.
	 */
	unsigned operands : 20;
} opcode_t;

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

/** Flag register index */
#define EVA_REG_FLAG 11
/** Frame pointer register index */
#define EVA_REG_FP 12
/** Stack pointer register index */
#define EVA_REG_SP	13
/** Comparison results register index */
#define EVA_REG_CMP 14
/** Program counter register index */
#define EVA_REG_PC 15

/**
 * @brief Conversion macro to "force" convert an op-code into an integer.
 *
 */
#define OPCODE2INT(x) *((int32_t *)&(x))
/**
 * @brief Conversion macro to "force" convert an op-code into an unsigned
 * integer.
 *
 */
#define OPCODE2UINT(x) *((uint32_t *)&(x))
/**
 * @brief Conversion macro to "force" convert an integer into an op-code.
 *
 */
#define INT2OPCODE(x) *((opcode_t *)&(x))
/**
 * @brief Conversion macro to "force" convert an unsigned integer into an
 * op-code.
 *
 */
#define UINT2OPCODE(x) *((opcode_t *)&(x))

/**
 * @brief Read an op-code from the input file in.
 *
 * @param out Output adress that will contain the read op-code.
 * @param in Input file object. Must be opened in binary read mode.
 * @return size_t
 */
size_t opcode_read(opcode_t *out, FILE *in);
/**
 * @brief Extract the register operands from the input op-code.
 *
 * @param op Input op-code
 * @param reg1 Output variable to register 1
 * @param reg2 Output variable to register 2
 */
void opcode_get_register_register(opcode_t *op, uint8_t *reg1, uint8_t *reg2);
/**
 * @brief Extrace the register and constant value operands from the input
 * op-code.
 *
 * @param op Input op-code
 * @param reg Output variable to register
 * @param val Output variable to constant value
 */
void opcode_get_register_value(opcode_t *op, uint8_t *reg, uint16_t *val);

/**
 * @brief Evaluates an op-code.
 *
 * @param op Op-code to evaluate
 * @param ram RAM array
 * @param registers Registers array
 */
void opcode_eval(opcode_t *op, opcode_t *ram, registers_t registers);

#endif
