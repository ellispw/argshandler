#include "argshandler.h"

struct ah_argshandler
ah_argshandler_create(char **args, int args_size, char **accepted_args, size_t accepted_args_size, size_t ignored) {
	struct ah_argshandler res;
	res.args = malloc(sizeof *res.args);
	res.args_size = 0;

	char **subargs = malloc(sizeof *subargs);
	size_t subargs_size = 0;

	int i;
	for (i = ignored; i < args_size; i++) {
		char *arg = args[i];
		int should_add_to_subargs = 1;
		
		int j;
		for (j = 0; j < accepted_args_size; j++) {
			char *accepted_arg = accepted_args[j];
		
			if (strcmp(accepted_arg, arg) == 0) {
				res.args_size = res.args_size + 1;
				res.args = realloc(res.args, sizeof *res.args * res.args_size);
				res.args[res.args_size - 1] = (struct ah_argshandler_arg) {accepted_arg, NULL, subargs_size};
				res.args[res.args_size - 1].subargs = malloc(sizeof *subargs * subargs_size);
				memcpy(res.args[res.args_size - 1].subargs, subargs, sizeof *subargs * subargs_size);
				subargs = realloc(subargs, sizeof *subargs);
				subargs_size = 0;
				should_add_to_subargs = 0;
			}
		}

		if (should_add_to_subargs) {
			subargs_size = subargs_size + 1;
			subargs = realloc(subargs, sizeof *subargs * subargs_size);
			subargs[subargs_size - 1] = arg;
		}
	}

	free(subargs);

	return res;
}

int
ah_argshandler_add_callback(struct ah_argshandler *argshandler, char *arg_name, ah_arghandler_callback callback) {
	int i;
	for (i = 0; i < argshandler->args_size; i++) {
		if (strcmp(argshandler->args[i].name, arg_name) == 0)
			(*callback)(argshandler->args[i]); 
	}
	
	return AH_ARGSHANDLER_OK;
}

void
ah_argshandler_destroy(struct ah_argshandler *argshandler) {
	int i;
	for (i = 0; i < argshandler->args_size; i++) {
		free(argshandler->args[i].subargs);
	}
	free(argshandler->args);
}
