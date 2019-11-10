/** Minimalist logging module, entirely preprocessor-based.
 * Based on
 * https://coderwall.com/p/v6u7jq/a-simplified-logging-system-using-macros
 */
#ifndef _H_LOG
#define _H_LOG
#include <string.h>
#include <time.h>

#define DLVL_QUIET 0
#define DLVL_ERROR 1
#define DLVL_INFO 2
#define DLVL_DEBUG 3

#ifndef LOG_LEVEL
#ifndef NDEBUG
#define LOG_LEVEL DLVL_DEBUG
#else
#define LOG_LEVEL DLVL_QUIET
#endif
#endif

/**
 * @brief Formats current time
 *
 */
static inline char *timenow();

#define DENABLED(LVL) LOG_LEVEL >= (LVL)

#define PRINT(format, ...) fprintf(stderr, format, __VA_ARGS__)
#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define LOG_FMT "[%s] %s %s %s:%d | "
#define LOG_ARGS(LOG_TAG) timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__
#define LOG(TAG, message, args...)                                             \
	PRINT(LOG_FMT message "\n", LOG_ARGS(TAG), ##args)

#if DENABLED(DLVL_DEBUG)
#define LOG_DEBUG(message, args...)                                            \
	PRINT(LOG_FMT message "\n", LOG_ARGS("DEBUG"), ##args)
#else
#define LOG_DEBUG(message, args...)
#endif

#if DENABLED(DLVL_INFO)
#define LOG_INFO(message, args...)                                             \
	PRINT(LOG_FMT message "\n", LOG_ARGS("INFO"), ##args)
#else
#define LOG_INFO(message, args...)
#endif

#if DENABLED(DLVL_ERROR)
#define LOG_ERROR(message, args...)                                            \
	PRINT(LOG_FMT message "\n", LOG_ARGS("ERROR"), ##args)
#else
#define LOG_ERROR(message, args...)
#endif

static inline char *timenow() {
	static char buffer[64];
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

	return buffer;
}

#endif
