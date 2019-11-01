#ifndef _H_CLI
#define _H_CLI

#include <stdint.h>
#include <stdio.h>
#include <string.h>
/**
 * @brief Structure containing arguments passed into (or left default by) the
 * program
 *
 */
typedef struct {
	/**
	 * @brief Size of the allocated RAM in blocks of 32 bits
	 *
	 */
	uint32_t ram_size;
	/**
	 * @brief Flag to turn on debugging features
	 *
	 */
	int debug;
	/**
	 * @brief Flag to output help message
	 *
	 */
	int help;
	/**
	 * @brief Only disassemble executable to stdout, don't execute.
	 *
	 */
	int disassemble;
	/**
	 * @brief Input file
	 *
	 */
	FILE *input;
} args_t;

/**
 * @brief Init arguments structure with default values
 *
 * @param args Structure to initialize
 */
void args_init(args_t *args);
/**
 * @brief Parse arguments from command line and fills in data into the arguments
 * structure. The structure will be properly initialized with default values
 * prior to filling it with passed arguments.
 *
 * @param args args_t structure into which to put arguments data
 * @param argc Number of arguments
 * @param argv Vector of string containing arguments
 */
void args_parse(args_t *args, int argc, char **argv);

#endif // _H_CLI
