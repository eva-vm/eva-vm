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
 *
 * @param op Opcode to disassemble.
 */
void disassemble(uint32_t *op);
/**
 * @brief Disassemble a program into a textual assembly representation into
 * file f.
 * ATTENTION: The resulting assembly code will often NOT be the same as the
 * input assembly code.
 *
 * @param f Output file, must be open in writable mode.
 * @param op Op-code to disassemble.
 */
void disassemble_file(FILE *f, uint32_t *op);
/**
 * @brief Disassemble a program into a textual assembly representation into the
 * output buffer.
 * ATTENTION: The resulting assembly code will often NOT be the same as the
 * input assembly code.
 *
 * @param out Output string buffer.
 * @param op Op-code to disassemble.
 */
void disassemble_str(char *out, uint32_t *op);

#endif
