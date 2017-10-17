#ifndef LOG_H_
#define LOG_H_

typedef enum LogLevelEnum { LLFATAL = 0, LLERR, LLWARN, LLINFO, LLDEBUG, LLTRACE } LogLevel;
typedef enum LogTargetEnum { LTNONE = 0, LTSTDOUT, LTSTDERR, LTFILE, LTSYSLOG } LogTarget;

void set_log_target(const LogTarget target);

void set_log_level(const LogLevel level);

void llog(const LogLevel level, const char *format, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));

void lfatal(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

void lerr(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

void lwarn(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

void linfo(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

void ldebug(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

void ltrace(const char *format, ...)
     __attribute__ ((__format__ (__printf__, 1, 2)));

#endif /* LOG_H_ */
