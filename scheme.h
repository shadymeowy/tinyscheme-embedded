/* SCHEME.H */

#ifndef _SCHEME_H
#define _SCHEME_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Default values for #define'd symbols
 */
#define SCHEME_EXPORT

#if USE_NO_FEATURES
#define USE_MATH 0
#define USE_STRING_PORTS 0
#define USE_ERROR_HOOK 0
#define USE_TRACING 0
#define USE_COLON_HOOK 0
#endif

#ifndef USE_MATH /* If math support is needed */
#define USE_MATH 0
#endif

#ifndef USE_STRING_PORTS /* Enable string ports */
#define USE_STRING_PORTS 1
#endif

#ifndef USE_TRACING
#define USE_TRACING 1
#endif

/* To force system errors through user-defined error handling (see *error-hook*) */
#ifndef USE_ERROR_HOOK
#define USE_ERROR_HOOK 1
#endif

#ifndef USE_COLON_HOOK /* Enable qualified qualifier */
#define USE_COLON_HOOK 1
#endif

#ifndef SHOW_ERROR_LINE /* Show error line in file */
#define SHOW_ERROR_LINE 1
#endif

typedef struct scheme scheme;
typedef struct cell *pointer;

typedef void *(*func_alloc)(size_t);
typedef void (*func_dealloc)(void *);

/* num, for generic arithmetic */
typedef struct num {
	char is_fixnum;
	union {
		long ivalue;
		double rvalue;
	} value;
} num;

SCHEME_EXPORT scheme *scheme_init_new(void);
SCHEME_EXPORT scheme *scheme_init_new_custom_alloc(func_alloc malloc,
						   func_dealloc free);
SCHEME_EXPORT int scheme_init(scheme *sc);
SCHEME_EXPORT int scheme_init_custom_alloc(scheme *sc, func_alloc,
					   func_dealloc);
SCHEME_EXPORT void scheme_deinit(scheme *sc);
void scheme_set_input_port_file(scheme *sc, FILE *fin);
void scheme_set_input_port_string(scheme *sc, char *start, char *past_the_end);
SCHEME_EXPORT void scheme_set_output_port_file(scheme *sc, FILE *fin);
void scheme_set_output_port_string(scheme *sc, char *start, char *past_the_end);
SCHEME_EXPORT void scheme_load_file(scheme *sc, FILE *fin);
SCHEME_EXPORT void scheme_load_named_file(scheme *sc, FILE *fin,
					  const char *filename);
SCHEME_EXPORT void scheme_load_string(scheme *sc, const char *cmd);
SCHEME_EXPORT pointer scheme_apply0(scheme *sc, const char *procname);
SCHEME_EXPORT pointer scheme_call(scheme *sc, pointer func, pointer args);
SCHEME_EXPORT pointer scheme_eval(scheme *sc, pointer obj);
void scheme_set_external_data(scheme *sc, void *p);
SCHEME_EXPORT void scheme_define(scheme *sc, pointer env, pointer symbol,
				 pointer value);

typedef pointer (*foreign_func)(scheme *, pointer);

pointer _cons(scheme *sc, pointer a, pointer b, int immutable);
pointer mk_integer(scheme *sc, long num);
pointer mk_real(scheme *sc, double num);
pointer mk_symbol(scheme *sc, const char *name);
pointer gensym(scheme *sc);
pointer mk_string(scheme *sc, const char *str);
pointer mk_counted_string(scheme *sc, const char *str, int len);
pointer mk_empty_string(scheme *sc, int len, char fill);
pointer mk_character(scheme *sc, int c);
pointer mk_foreign_func(scheme *sc, foreign_func f);
void putstr(scheme *sc, const char *s);
int list_length(scheme *sc, pointer a);
int eqv(pointer a, pointer b);

/*#define setimmutable(p)  typeflag(p) |= T_IMMUTABLE*/

typedef struct scheme_registerable {
	foreign_func f;
	const char *name;
} scheme_registerable;

void scheme_register_foreign_func_list(scheme *sc, scheme_registerable *list,
				       int n);
void scheme_register_foreign_func(scheme *sc, scheme_registerable *sr);

#ifdef __cplusplus
}
#endif

#endif

/*
Local variables:
c-file-style: "k&r"
End:
*/
