#ifndef __SPDLOGC_H__
#define __SPDLOGC_H__

#define SPDLOGC_API extern "C"

#include <spdlog/common.h>

typedef void *(*spdlogc_allocator_t)(size_t);
typedef void (*spdlogc_deleter_t)(void *);

enum SPDLOGC_BOOL : uint8_t { SPDLOGC_FALSE = 0, SPDLOGC_TRUE };

SPDLOGC_API void spdlogc_set_pattern(const char *pattern);

SPDLOGC_API void spdlogc_set_level(const char *logger_name, int level);

SPDLOGC_API void spdlogc_set_allocator(spdlogc_allocator_t allocator,
                                       spdlogc_deleter_t deleter);

SPDLOGC_API void spdlogc_append_stdout_sink_to_logger(const char *logger_name);

SPDLOGC_API void
spdlogc_append_basic_file_sink_to_logger(const char *logger_name,
                                         const char *filename,
                                         SPDLOGC_BOOL truncate = SPDLOGC_FALSE);

SPDLOGC_API void spdlogc_log_trace(const char *logger_name, const char *fmt,
                                   ...);

SPDLOGC_API void spdlogc_log_debug(const char *logger_name, const char *fmt,
                                   ...);

SPDLOGC_API void spdlogc_log_info(const char *logger_name, const char *fmt,
                                  ...);

SPDLOGC_API void spdlogc_log_warn(const char *logger_name, const char *fmt,
                                  ...);

SPDLOGC_API void spdlogc_log_error(const char *logger_name, const char *fmt,
                                   ...);

SPDLOGC_API void spdlogc_log_critical(const char *logger_name, const char *fmt,
                                      ...);

#endif // __SPDLOGC_H__