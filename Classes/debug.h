#ifndef DEBUG_H
#define DEBUG_H

#define stringify(x)	#x

#define dbgInt(x, ...)		do { printf("%s:%d", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgChar(x, ...)		do { printf("%s:%c", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgFloat(x, ...)	do { printf("%s:%f", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgDouble(x, ...)	do { printf("%s:%f", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgString(x, ...)	do { printf("%s:%s", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgPointer(x, ...)	do { printf("%s:%p%s", stringify(x), x, ##__VA_ARGS__); } while (0)
#define dbgAll(x, ...)		do { printf("%s:%p\t%c\t%d\t%f\t%s", stringify(x), x, x, x, x, x); } while (0)

#include <stdio.h>

#endif
