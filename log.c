#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

#include "log.h"

typedef void (*log_fn)(LogLevel level, const char *format, va_list ap);

void
log_syslog(LogLevel level, const char *format, va_list ap);

void
log_file(LogLevel level, const char *format, va_list ap);

FILE *lfile;

log_fn lfn;

LogLevel logLevel;

void
set_log_target(const LogTarget target) {
	lfn = NULL;

	switch (target) {
		case LTNONE:
			lfn = NULL;
			break;

		case LTSTDOUT:
			lfn = log_file;
			lfile = stdout;
			break;

		case LTSTDERR:
			lfn = log_file;
			lfile = stderr;
			break;

		case LTFILE:
			fprintf(stderr, "LTFILE LogTarget not supported\n");
			break;

		case LTSYSLOG:
			lfn = log_syslog;
			break;

		default:
			fprintf(stderr, "Unknown %d LogTarget\n", target);
	}

	if (NULL == lfn) {
		fprintf(stderr, "Log defaulting to stderr\n");

		lfn = log_file;
		lfile = stderr;
	}
}

void
set_log_level(const LogLevel level)
{
	logLevel = level;
}

void
llog(const LogLevel level, const char *format, ...)
{
	va_list ap;

	if (level > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(level, format, ap);

	va_end(ap);
}

void
lfatal(const char *format, ...)
{
	va_list ap;

	if (LLFATAL > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLFATAL, format, ap);

	va_end(ap);
}

void
lerr(const char *format, ...)
{
	va_list ap;

	if (LLERR > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLERR, format, ap);

	va_end(ap);
}

void
lwarn(const char *format, ...)
{
	va_list ap;

	if (LLWARN > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLWARN, format, ap);

	va_end(ap);
}

void
linfo(const char *format, ...)
{
	va_list ap;

	if (LLINFO > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLINFO, format, ap);

	va_end(ap);
}

void
ldebug(const char *format, ...)
{
	va_list ap;

	if (LLDEBUG > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLDEBUG, format, ap);

	va_end(ap);
}

void
ltrace(const char *format, ...)
{
	va_list ap;

	if (LLTRACE > logLevel || NULL == lfn) {
		return;
	}

	va_start(ap, format);

	lfn(LLTRACE, format, ap);

	va_end(ap);
}

static inline
int
logLevelToPriority(LogLevel level) {
	switch (level) {
		case LLFATAL:
			return LOG_CRIT;

		case LLERR:
			return LOG_ERR;

		case LLWARN:
			return LOG_WARNING;

		case LLINFO:
			return LOG_NOTICE;

		case LLDEBUG:
			return LOG_DEBUG;

		default:
			// error: unknown value
			return LOG_CRIT;
	}
}

void
log_syslog(LogLevel level, const char *format, va_list ap)
{
	vsyslog(logLevelToPriority(level), format, ap);
}

char logbuf[8192];

void
log_file(LogLevel level, const char *format, va_list ap)
{
	vsnprintf(logbuf, sizeof(logbuf), format, ap);
	logbuf[sizeof(logbuf) - 1] = '\0';
	fprintf(lfile, "%s\n", logbuf);
	fflush(lfile);
}
