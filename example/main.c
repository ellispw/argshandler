#include <stdio.h>

#include "../argshandler/argshandler.h"

static void _callback(struct ah_argshandler_arg arg) {
	printf("Argument name: %s\n", arg.name);		
	printf("# of subargs: %zu\n", arg.subargs_size);
	int i;
	for (i = 0; i < arg.subargs_size; i++)
		printf("Subarg %d: %s\n", i, arg.subargs[i]);
}

int main(int argc, char **argv) { 
	char *accepted_args[2] = {"-put", "-o"};
	struct ah_argshandler handler = ah_argshandler_create(argv, argc, accepted_args, 2, 1);	

	ah_argshandler_add_callback(&handler, accepted_args[0], _callback);
	ah_argshandler_add_callback(&handler, accepted_args[1], _callback);
 	ah_argshandler_destroy(&handler);
}
