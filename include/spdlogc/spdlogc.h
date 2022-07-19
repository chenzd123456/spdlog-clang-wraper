#ifndef __SPDLOGC_H__
#define __SPDLOGC_H__

#define SPDLOGC_API extern "C"

#include <spdlog/common.h>

typedef void *(*spdlogc_allocator_t)(size_t);
typedef void (*spdlogc_deleter_t)(void *);

#define SPDLOGC_TRACE(logger_name, fmt_, ...)                                  \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)
#define SPDLOGC_DEBUG(logger_name, fmt_, ...)                                  \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)
#define SPDLOGC_INFO(logger_name, fmt_, ...)                                   \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)
#define SPDLOGC_WARNNING(logger_name, fmt_, ...)                               \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)
#define SPDLOGC_ERROR(logger_name, fmt_, ...)                                  \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)
#define SPDLOGC_CRITICAL(logger_name, fmt_, ...)                               \
    spdlogc_log(spdlogc_level_trace, logger_name, fmt_, __VA_ARGS__)

enum SPDLOGC_LEVEL : int {
    spdlogc_level_trace = SPDLOG_LEVEL_TRACE,
    spdlogc_level_debug = SPDLOG_LEVEL_DEBUG,
    spdlogc_level_info = SPDLOG_LEVEL_INFO,
    spdlogc_level_warn = SPDLOG_LEVEL_WARN,
    spdlogc_level_err = SPDLOG_LEVEL_ERROR,
    spdlogc_level_critical = SPDLOG_LEVEL_CRITICAL,
    spdlogc_level_off = SPDLOG_LEVEL_OFF
};

enum SPDLOGC_BOOL : uint8_t { SPDLOGC_FALSE = 0, SPDLOGC_TRUE };

SPDLOGC_API void spdlogc_init_thread_pool(size_t queue_size, size_t n_threads);

SPDLOGC_API void spdlogc_set_pattern(const char *logger_name,
                                     const char *pattern);

SPDLOGC_API void spdlogc_set_level(const char *logger_name,
                                   SPDLOGC_LEVEL level);

SPDLOGC_API void spdlogc_set_allocator(spdlogc_allocator_t allocator,
                                       spdlogc_deleter_t deleter);

SPDLOGC_API void spdlogc_create_sync_logger(const char *logger_name);

SPDLOGC_API void spdlogc_create_async_logger(const char *logger_name);

SPDLOGC_API void spdlogc_append_stdout_sink_to_logger(const char *logger_name);

SPDLOGC_API void
spdlogc_append_basic_file_sink_to_logger(const char *logger_name,
                                         const char *filename,
                                         SPDLOGC_BOOL truncate = SPDLOGC_FALSE);

SPDLOGC_API void spdlogc_log(SPDLOGC_LEVEL level, const char *logger_name,
                             const char *fmt, ...);

#endif // __SPDLOGC_H__