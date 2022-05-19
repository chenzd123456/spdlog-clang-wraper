#include "spdlogc/spdlogc.h"

#include <memory>
#include <stdarg.h>

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

constexpr size_t SPDLOGC_BUF_SIZE = 256;

#define IF_NULL_RETURN(ptr)                                                    \
    if (ptr == nullptr) {                                                      \
        return;                                                                \
    }

void *__default_allocator(size_t size) { return malloc(size); }

void __default_deleter(void *ptr) { free(ptr); }

static size_t __buf_size = SPDLOGC_BUF_SIZE;
static spdlogc_allocator_t __allocator = &__default_allocator;
static spdlogc_deleter_t __deleter = &__default_deleter;

bool __ToBool(SPDLOGC_BOOL bool_) { return bool_ == SPDLOGC_TRUE; }

SPDLOGC_API void spdlogc_set_allocator(spdlogc_allocator_t allocator,
                                       spdlogc_deleter_t deleter) {
    IF_NULL_RETURN(allocator);
    IF_NULL_RETURN(deleter);
    __allocator = allocator;
    __deleter = deleter;
}

std::shared_ptr<spdlog::logger> __GetLogger(const char *logger_name) {
    std::shared_ptr<spdlog::logger> logger = spdlog::get(logger_name);

    if (!logger) {
        logger = std::make_shared<spdlog::logger>(logger_name);
        spdlog::register_logger(logger);
    }

    return logger;
}

SPDLOGC_API void spdlogc_set_pattern(const char *pattern) {
    IF_NULL_RETURN(pattern);
    spdlog::set_pattern(pattern);
}

SPDLOGC_API void spdlogc_set_level(const char *logger_name, int level) {
    IF_NULL_RETURN(logger_name);
    __GetLogger(logger_name)
        ->set_level(static_cast<spdlog::level::level_enum>(level));
}

SPDLOGC_API void spdlogc_append_stdout_sink_to_logger(const char *logger_name) {
    IF_NULL_RETURN(logger_name);
    __GetLogger(logger_name)
        ->sinks()
        .push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
}

SPDLOGC_API void spdlogc_append_basic_file_sink_to_logger(
    const char *logger_name, const char *filename, SPDLOGC_BOOL truncate) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(filename);
    __GetLogger(logger_name)
        ->sinks()
        .push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            filename, __ToBool(truncate)));
}

SPDLOGC_API void spdlogc_log_trace(const char *logger_name, const char *fmt,
                                   ...) {
    va_list args;
    va_start(args, fmt);
    SPDLOG_LOGGER_TRACE(__GetLogger(logger_name), fmt, args);
}

SPDLOGC_API void spdlogc_log_debug(const char *logger_name, const char *fmt,
                                   ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);
    char *buf = static_cast<char *>(__allocator(__buf_size));
    IF_NULL_RETURN(buf);
    memset(buf, __buf_size, 0x00);
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, __buf_size, fmt, args);
    va_end(args);
    __GetLogger(logger_name)->debug(buf);
    __deleter(buf);
}

SPDLOGC_API void spdlogc_log_info(const char *logger_name, const char *fmt,
                                  ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);
    char *buf = static_cast<char *>(__allocator(__buf_size));
    IF_NULL_RETURN(buf);
    memset(buf, __buf_size, 0x00);
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, __buf_size, fmt, args);
    va_end(args);
    __GetLogger(logger_name)->info(buf);
    __deleter(buf);
}

SPDLOGC_API void spdlogc_log_warn(const char *logger_name, const char *fmt,
                                  ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);
    char *buf = static_cast<char *>(__allocator(__buf_size));
    IF_NULL_RETURN(buf);
    memset(buf, __buf_size, 0x00);
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, __buf_size, fmt, args);
    va_end(args);
    __GetLogger(logger_name)->warn(buf);
    __deleter(buf);
}

SPDLOGC_API void spdlogc_log_error(const char *logger_name, const char *fmt,
                                   ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);
    char *buf = static_cast<char *>(__allocator(__buf_size));
    IF_NULL_RETURN(buf);
    memset(buf, __buf_size, 0x00);
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, __buf_size, fmt, args);
    va_end(args);
    __GetLogger(logger_name)->error(buf);
    __deleter(buf);
}

SPDLOGC_API void spdlogc_log_critical(const char *logger_name, const char *fmt,
                                      ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);
    char *buf = static_cast<char *>(__allocator(__buf_size));
    IF_NULL_RETURN(buf);
    memset(buf, __buf_size, 0x00);
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, __buf_size, fmt, args);
    va_end(args);
    __GetLogger(logger_name)->critical(buf);
    __deleter(buf);
}
