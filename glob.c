#include <yasl/yasl.h>

#include <stdio.h>
#include <glob.h>

int YASL_glob(struct YASL_State *S) {
	const char *s = YASL_popcstr(S);

	glob_t paths;
	int res = glob(s, GLOB_ERR, NULL, &paths);
	if (res != 0) {
		YASL_pushundef(S);
		return 1;
	}

	YASL_pushlist(S);

	for (int idx = 0; idx < paths.gl_pathc; idx++) {
		YASL_pushzstr(S, paths.gl_pathv[idx]);
		YASL_listpush(S);
	}

	globfree(&paths);
	return 1;
}

int YASL_load_dyn_lib(struct YASL_State *S) {
	YASL_pushcfunction(S, YASL_glob, 1);

	return 1;
}
