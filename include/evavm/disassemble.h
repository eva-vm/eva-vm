#ifndef _H_DISASSEMBLE
#define _H_DISASSEMBLE
#include <evavm/eva.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Disassemble a program into a textual assembly representation into
 * stdout.
 * ATTENTION: The resulting assembly code will often NOT be the same as the
 * input assembly code.
 * @param op Opcode to disassemble.
 */
void disassemble(opcode_t *op);
void disassemble_file(FILE *f, opcode_t *op);
void disassemble_str(char *out, opcode_t *op);

#endif
