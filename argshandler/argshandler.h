#ifndef AH_ARGSHANDLER_H
#define AH_ARGSHANDLER_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define AH_ARGSHANDLER_OK	1
#define AH_ARGSHANDLER_ERR 0

struct ah_argshandler_arg {
	char *name;
	char **subargs;
	size_t subargs_size;
};

typedef void (*ah_arghandler_callback)(struct ah_argshandler_arg);

struct ah_argshandler {
	struct ah_argshandler_arg *args;
	int args_size;
};

extern struct ah_argshandler
ah_argshandler_create(char **args, int args_size, char **accepted_args, size_t accepted_args_size, size_t ignored /*how many args to ignore*/);

extern int
ah_argshandler_add_callback(struct ah_argshandler *argshandler, char *arg_name, ah_arghandler_callback callback);

extern void
ah_argshandler_destroy(struct ah_argshandler *argshandler);

#endif //AH_ARGSHANDLER_H
