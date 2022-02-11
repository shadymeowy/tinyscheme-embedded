// gcc scheme.c -lm example.c -o example.out

#include "scheme.h"

int main(int argc, char **argv)
{
	scheme *sc;
	if (!(sc = scheme_init_new())) {
		return 2;
	}

	scheme_set_input_port_file(sc, stdin);
	scheme_set_output_port_file(sc, stdout);
	scheme_load_string(sc, "(display \"Hello, World!\")");
	scheme_deinit(sc);

	return 0;
}