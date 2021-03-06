#ifndef	INFODUMPFO_VERSION_INCLUDED
#define INFODUMPFO_VERSION_INCLUDED

#define MAKE_STR_HELPER(x) #x
#define MAKE_STR(x) MAKE_STR_HELPER(x)

#define INFODUMPFO_VERSION_MAJOR	1
#define INFODUMPFO_VERSION_MINOR	0
#define INFODUMPFO_VERSION_PATCH	0
#define INFODUMPFO_VERSION_BETA		0
#define INFODUMPFO_VERSION_VERSTRING	MAKE_STR(INFODUMPFO_VERSION_MAJOR) "." MAKE_STR(INFODUMPFO_VERSION_MINOR) "." MAKE_STR(INFODUMPFO_VERSION_PATCH) "." MAKE_STR(INFODUMPFO_VERSION_BETA)

#endif
