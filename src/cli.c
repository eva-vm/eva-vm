#include "cli.h"
#include <evavm/eva.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void args_init(args_t *args) {
	args->debug = 0;
	args->ram_size =
	    256 * 1024 * 1024 / sizeof(opcode_t); // 1 instruction is 4 bits long
	args->help = 0;
	args->disassemble = 0;
	args->input = stdin;
}

void args_parse(args_t *args, int argc, char **argv) {
	args_init(args);
	int i = 1;
	while (i < argc) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
			args->help = 1;
		else if (strcmp(argv[i], "--debug") == 0)
			args->debug = 1;
		else if (strcmp(argv[i], "--ram-size") == 0) {
			sscanf(argv[i++], "%d", &args->ram_size);
			args->ram_size *= 1024 * 1024 / sizeof(opcode_t);
		} else if (strcmp(argv[i], "--disassemble") == 0)
			args->disassemble = 1;

		else {
			if(strcmp(argv[i], "-") == 0)
				args->input = stdin;
			else
				args->input = fopen(argv[i], "rb");
		}
		i++;
	}
}
