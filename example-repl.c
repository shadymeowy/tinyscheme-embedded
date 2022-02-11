// gcc scheme.c -lreadline example-repl.c -o example-repl.out

#include "scheme.h"
#include "scheme-private.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv)
{
	scheme *sc;
	pointer write;
    pointer args;

	if (!(sc = scheme_init_new())) {
		return 2;
	}

	scheme_set_input_port_file(sc, stdin);
	scheme_set_output_port_file(sc, stdout);

	write = scheme_eval(sc, mk_symbol(sc, "write"));

	while (1) {
        char *cmd = readline("scheme> ");
        add_history(cmd);
		scheme_load_string(sc, cmd);
        free(cmd);
		args = cons(sc, sc->value, sc->NIL);
		scheme_call(sc, write, args);
		printf("\n");
	}
	scheme_deinit(sc);

	return 0;
}