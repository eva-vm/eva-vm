#include <evatest/test.h>
#include "../src/cli.h"
#include "../src/eva.h"

int main() {
	char *args1[] = {"<exe>", "--debug"};
	char *args2[] = {"<exe>", "-h"};
	char *args3[] = {"<exe>", "file.eva"};
	char *args4[] = {"<exe>", "--ram-size", "500", "file.eva"};
	INIT_TEST;
	args_t parsed;
	args_parse(&parsed, 2, args1);
	TEST(parsed.debug);
	TEST(!parsed.help);

	args_parse(&parsed, 2, args2);
	TEST(!parsed.debug);
	TEST(parsed.help);

	args_parse(&parsed, 2, args3);
	TEST(!parsed.debug);
	TEST(!parsed.help);
	TEST(parsed.ram_size == 256 * 1024 * 1024 / sizeof(opcode_t));
	TEST(parsed.input != NULL);

	args_parse(&parsed, 4, args4);
	TEST(!parsed.debug);
	TEST(!parsed.help);
	TEST(parsed.ram_size == 500 * 1024 * 1024 / sizeof(opcode_t));
	TEST(parsed.input != NULL);
	END_TEST;
}
