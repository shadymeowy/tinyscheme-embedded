#include "scheme.h"
#include "scheme-private.h"

int custom_print(int a)
{
	printf("%d\n", a);
	return 0;
}

pointer custom_print_func(scheme *sc, pointer args)
{
	pointer a = pair_car(args);
	int r = custom_print(ivalue(a));
	return r ? sc->T : sc->F;
}

pointer custom_print2_func(scheme *sc, pointer args)
{
	pointer a = car(args);
	int r = custom_print(ivalue(a) * 2);
	return r ? sc->T : sc->F;
}

int main(int argc, char **argv)
{
	scheme sc;
	if (!scheme_init(&sc)) {
		return 2;
	}
	scheme_set_input_port_file(&sc, stdin);
	scheme_set_output_port_file(&sc, stdout);
	scheme_define(&sc, sc.global_env, mk_symbol(&sc, "custom-print"),
		      mk_foreign_func(&sc, custom_print_func));

	scheme_registerable custom_print2_func_reg = {
		custom_print2_func,
		"custom-print2",
	};
	scheme_register_foreign_func(&sc, &custom_print2_func_reg);

	scheme_load_string(&sc,
			   "(define (fun a b) (custom-print (* a b)) (+ a b))");

	pointer func = scheme_eval(&sc, mk_symbol(&sc, "fun"));
	pointer args = cons(&sc, mk_integer(&sc, 3),
			    cons(&sc, mk_integer(&sc, 5), sc.NIL));
	pointer result = scheme_call(&sc, func, args);

	func = scheme_eval(&sc, mk_symbol(&sc, "custom-print2"));
	args = cons(&sc, result, sc.NIL);
	scheme_call(&sc, func, args);

	scheme_deinit(&sc);

	return 0;
}