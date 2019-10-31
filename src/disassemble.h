#ifndef _H_DISASSEMBLE
#define _H_DISASSEMBLE

#include "eva.h"

/**
 * @brief Disassemble a program into a textual assembly representation into
 * stdout.
 * ATTENTION: The resulting assembly code will often NOT be the same as the
 * input assembly code.
 * @param op Opcode to disassemble.
 */
void disassemble(opcode_t *op);

#endif
