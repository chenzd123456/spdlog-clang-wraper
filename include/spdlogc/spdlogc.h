#ifndef __SPDLOGC_H__
#define __SPDLOGC_H__

#define SPDLOGC_API extern "C"

#include <spdlog/common.h>

typedef void *(*spdlogc_allocator_t)(size_t);
typedef void (*spdlogc_deleter_t)(void *);

#define SPDLOGC_TRACE(logger_name, fmt_, ...)                                  \
    spdlogc_log(SPDLOGC_LEVEL_TRACE, logger_name, fmt_, ##__VA_ARGS__)
#define SPDLOGC_DEBUG(logger_name, fmt_, ...)                                  \
    spdlogc_log(SPDLOGC_LEVEL_DEBUG, logger_name, fmt_, ##__VA_ARGS__)
#define SPDLOGC_INFO(logger_name, fmt_, ...)                                   \
    spdlogc_log(SPDLOGC_LEVEL_INFO, logger_name, fmt_, ##__VA_ARGS__)
#define SPDLOGC_WARN(logger_name, fmt_, ...)                                   \
    spdlogc_log(SPDLOGC_LEVEL_WARN, logger_name, fmt_, ##__VA_ARGS__)
#define SPDLOGC_ERROR(logger_name, fmt_, ...)                                  \
    spdlogc_log(SPDLOGC_LEVEL_ERROR, logger_name, fmt_, ##__VA_ARGS__)
#define SPDLOGC_CRITICAL(logger_name, fmt_, ...)                               \
    spdlogc_log(SPDLOGC_LEVEL_CRITICAL, logger_name, fmt_, ##__VA_ARGS__)

enum SPDLOGC_LEVEL : int {
    SPDLOGC_LEVEL_TRACE = SPDLOG_LEVEL_TRACE,
    SPDLOGC_LEVEL_DEBUG = SPDLOG_LEVEL_DEBUG,
    SPDLOGC_LEVEL_INFO = SPDLOG_LEVEL_INFO,
    SPDLOGC_LEVEL_WARN = SPDLOG_LEVEL_WARN,
    SPDLOGC_LEVEL_ERROR = SPDLOG_LEVEL_ERROR,
    SPDLOGC_LEVEL_CRITICAL = SPDLOG_LEVEL_CRITICAL,
    SPDLOGC_LEVEL_OFF = SPDLOG_LEVEL_OFF
};

enum SPDLOGC_BOOL : uint8_t { SPDLOGC_FALSE = 0, SPDLOGC_TRUE };

SPDLOGC_API void spdlogc_init_thread_pool(size_t queue_size, size_t n_threads);

SPDLOGC_API void spdlogc_set_sink_pattern(const char *logger_name,
                                          const char *pattern);

SPDLOGC_API void spdlogc_set_logger_level(const char *logger_name,
                                          SPDLOGC_LEVEL level);

SPDLOGC_API void spdlogc_set_allocator(spdlogc_allocator_t allocator,
                                       spdlogc_deleter_t deleter);

SPDLOGC_API void spdlogc_create_sync_logger(const char *logger_name);

SPDLOGC_API void spdlogc_create_async_logger(const char *logger_name);

SPDLOGC_API void
spdlogc_create_basic_file_sink(const char *sink_name, const char *filename,
                               SPDLOGC_BOOL truncate = SPDLOGC_FALSE);

SPDLOGC_API void
spdlogc_create_rotating_file_sink(const char *sink_name, const char *filename,
                                  std::size_t max_size, std::size_t max_files,
                                  SPDLOGC_BOOL rotate_on_open = SPDLOGC_FALSE);

SPDLOGC_API void spdlogc_create_stdout_sink(const char *sink_name);

SPDLOGC_API void spdlogc_append_sink_to_logger(const char *logger_name,
                                               const char *sink_name);

SPDLOGC_API void spdlogc_remove_sink_from_logger(const char *logger_name,
                                                 const char *sink_name);

SPDLOGC_API void spdlogc_log(SPDLOGC_LEVEL level, const char *logger_name,
                             const char *fmt, ...);

#endif // __SPDLOGC_H__