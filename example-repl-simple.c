// gcc scheme.c example-repl-simple.c -o example-repl-simple.out

#include "scheme.h"
#include "scheme-private.h"

void read_line(FILE *in, char *buf, int size)
{
	int i = 0;
	while (i < size - 1) {
		int c = fgetc(in);
		if (c == EOF) {
			break;
		}
		if (c == '\n') {
			break;
		}
		buf[i++] = c;
	}
	buf[i] = '\0';
}

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
		char buf[1024];
		printf("scheme> ");
		read_line(stdin, buf, sizeof(buf));
		scheme_load_string(sc, buf);
		args = cons(sc, sc->value, sc->NIL);
		scheme_call(sc, write, args);
		printf("\n");
	}
	scheme_deinit(sc);

	return 0;
}