#include "cli.h"
#include "disassemble.h"
#include "eva.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_help(char *argv0) {
	printf("Usage: %.50s [-h] [--debug] [--ram-size SIZE] FILE\n", argv0);
	printf("\n");
	printf("INPUT\t\tFile to execute by the Eva VM");
	printf("-h\t\tPrint this help screen and exit\n");
	printf("--debug\t\tRun file in debug mode (allows settings breakpoints and "
	       "printing memory\n");
	printf(
	    "--ram-size SIZE\tSets the size of allocated RAM space to SIZE bytes");
}

int main(int argc, char **argv) {
	args_t args;
	registers_t registrers;
	opcode_t *ram;
	uint8_t bits[sizeof(opcode_t)];
	int instr_count = 0, i = 0;

	args_parse(&args, argc, argv);

	if (args.help) {
		print_help(argv[0]);
		return 0;
	}

	ram = malloc(sizeof(opcode_t) * args.ram_size);

	while (opcode_read(ram + instr_count, args.input) &&
	       instr_count < args.ram_size) {
		instr_count++;
	}
	printf("Read %d instructions into memory\n", instr_count);

	for (i = 0; i < instr_count; i++) {
		disassemble(ram + i);
	}
	free(ram);
	return 0;
}
