#ifndef SIGNALCATCHER_H
#define SIGNALCATCHER_H

extern long SCCurrentLine;
extern char *SCCurrentFile;
#define SC	 do { SCCurrentLine = __LINE__; SCCurrentFile = __FILE__; } while (0)

#endif //SIGNALCATCHER_H
