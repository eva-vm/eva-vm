#include "cli.h"
#include <evavm/disassemble.h>
#include <evavm/eva.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_help(char *argv0) {
	printf("Usage: %.50s [-h] [--debug] [--ram-size SIZE] FILE\n", argv0);
	printf("\n");
	printf("FILE\t\tFile to execute by the Eva VM\n");
	printf("-h\t\tPrint this help screen and exit\n");
	printf("--debug\t\tRun file in debug mode (allows settings breakpoints and "
	       "printing memory\n");
	printf(
	    "--ram-size SIZE\tSets the size of allocated RAM space to SIZE bytes");
}

int main(int argc, char **argv) {
	args_t args;
	opcode_t *ram;
	int instr_count = 0;

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
	fprintf(stderr, "Read %d instructions into memory\n", instr_count);
	if (args.disassemble) {

		for (int i = 0; i < instr_count; i++) {
			disassemble(ram + i);
		}
	} else {
		// RUN THE THING!
		registers_t registers = {0};

		while (registers[EVA_REG_PC] < instr_count) {
			opcode_eval(ram + registers[EVA_REG_PC], ram, registers);
			registers[EVA_REG_PC]++;
		}
	}
	free(ram);
	return 0;
}
