#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

long SCCurrentLine;
char *SCCurrentFile;

void SCCatch(int sig_num) {
	char *f = NULL;
	switch (sig_num) {
	case SIGHUP:	/* hangup */
		f = "hang up";
		break;
	case SIGINT:	/* interrupt */
		f = "interrupt";
		break;
	case SIGQUIT:	/* quit */
		f = "quit";
		break;
	case SIGILL:	/* illegal instruction (not reset when caught) */
		f = "illegal instruction";
		break;
	case SIGTRAP:	/* trace trap (not reset when caught) */
		f = "trace trap";
		break;
	case SIGABRT:	/* abort() */
		f = "abort";
		break;

#if  (defined(_POSIX_C_SOURCE) && !defined(_DARWIN_C_SOURCE))
	case SIGPOLL:	/* pollable event ([XSR] generated, not supported) */
		f = "pollable event";
		break;

#else	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
#ifndef SIGABRT
	case SIGIOT:	/* compatibility */
		f = "sigabrt (compatibility)";
		break;
#endif
	case SIGEMT:	/* EMT instruction */
		f = "EMT instruction";
		break;
#endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */

	case SIGFPE:	/* floating point exception */
		f = "floating point exception";
		break;
	case SIGKILL:	/* kill (cannot be caught or ignored) */
		f = "kill";
		break;
	case SIGBUS:	/* bus error */
		f = "bus error";
		break;
	case SIGSEGV:	/* segmentation violation */
		f = "segmentation violation";
		break;
	case SIGSYS:	/* bad argument to system call */
		f = "bad argument system call";
		break;
	case SIGPIPE:	/* write on a pipe with no one to read it */
		f = "readerless pipe write";
		break;
	case SIGALRM:	/* alarm clock */
		f = "alarm clock";
		break;
	case SIGTERM:	/* software termination signal from kill */
		f = "SW termination signal from kill";
		break;
	case SIGURG:	/* urgent condition on IO channel */
		f = "urgent condition on IO channel";
		break;
	case SIGSTOP:	/* sendable stop signal not from tty */
		f = "stop. Hammertime";
		break;
	case SIGTSTP:	/* stop signal from tty */
		f = "stop. Hammertime (TTY)";
		break;
	case SIGCONT:	/* continue a stopped process */
		f = "continue";
		break;
	case SIGCHLD:	/* to parent on child stop or exit */
		f = "childless";
		break;
	case SIGTTIN:	/* to readers pgrp upon background tty read */
		f = "TTIN";
		break;
	case SIGTTOU:	/* like TTIN for output if (tp->t_local&LTOSTOP) */
		f = "TTOUT";
		break;

#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
	case SIGIO: /* input/output possible signal */
		f = "I/O possible signal";
		break;
#endif

	case SIGXCPU:	/* exceeded CPU time limit */
		f = "exceeded CPU time limit";
		break;
	case SIGXFSZ:	/* exceeded file size limit */
		f = "exceeded file size limit";
		break;
	case SIGVTALRM: /* virtual time alarm */
		f = "virtual time alarm";
		break;
	case SIGPROF:	/* profiling time alarm */
		f = "profiling time alarm";
		break;

#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
	case SIGWINCH:	/* window size changes */
		f = "window size change";
		break;
	case SIGINFO:	/* information request */
		f = "information request";
		break;
#endif

	case SIGUSR1:	/* user defined signal 1 */
		f = "usr signal 1";
		break;
	case SIGUSR2:	/* user defined signal 2 */
		f = "usr signal 2";
		break;
	}

	fprintf(stderr, "@%s:%ld: %s\n", SCCurrentFile, SCCurrentLine, f);

	exit(1);
}

void __attribute__((constructor)) SCInit(void) {
	int sig[] = {
SIGHUP,
SIGINT,
SIGQUIT,
SIGILL,
SIGTRAP,
SIGABRT,
#if  (defined(_POSIX_C_SOURCE) && !defined(_DARWIN_C_SOURCE))
SIGPOLL,
#else	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
SIGIOT,
SIGEMT,
#endif	/* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
SIGFPE,
SIGKILL,
SIGBUS,
SIGSEGV,
SIGSYS,
SIGPIPE,
SIGALRM,
SIGTERM,
SIGURG,
SIGSTOP,
SIGTSTP,
SIGCONT,
SIGCHLD,
SIGTTIN,
SIGTTOU,
#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
SIGIO,
#endif
SIGXCPU,
SIGXFSZ,
SIGVTALRM,
SIGPROF,
#if  (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
SIGWINCH,
SIGINFO,
#endif
SIGUSR1,
SIGUSR2,
	};
	for (int i = 0; i < sizeof(sig)/sizeof(int *); i++) {
		signal(sig[i], SCCatch);
	}
}
