#include "spdlogc/spdlogc.h"

#include <memory>
#include <unordered_map>

#include <stdarg.h>

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
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
static std::unordered_map<std::string, spdlog::sink_ptr> sinks_map;

bool __ToBool(SPDLOGC_BOOL bool_) { return bool_ == SPDLOGC_TRUE; }

SPDLOGC_API void spdlogc_set_allocator(spdlogc_allocator_t allocator,
                                       spdlogc_deleter_t deleter) {
    IF_NULL_RETURN(allocator);
    IF_NULL_RETURN(deleter);
    __allocator = allocator;
    __deleter = deleter;
}

SPDLOGC_API void spdlogc_init_thread_pool(size_t queue_size, size_t n_threads) {
    spdlog::init_thread_pool(queue_size, n_threads);
}

SPDLOGC_API void spdlogc_create_sync_logger(const char *logger_name) {
    IF_NULL_RETURN(logger_name);
    auto logger = spdlog::get(logger_name);
    if (logger) {
        spdlog::drop(logger_name);
    }
    logger = std::make_shared<spdlog::logger>(logger_name);
    spdlog::register_logger(logger);
}

SPDLOGC_API void spdlogc_create_async_logger(const char *logger_name) {
    IF_NULL_RETURN(logger_name);
    auto logger = spdlog::get(logger_name);
    if (logger) {
        spdlog::drop(logger_name);
    }
    std::vector<spdlog::sink_ptr> sinks;
    logger = std::make_shared<spdlog::async_logger>(
        logger_name, sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);
    spdlog::register_logger(logger);
}

SPDLOGC_API void spdlogc_set_sink_pattern(const char *sink_name,
                                          const char *pattern) {
    IF_NULL_RETURN(sink_name);
    IF_NULL_RETURN(pattern);
    auto sink_it = sinks_map.find(sink_name);
    if (sink_it != sinks_map.end()) {
        sink_it->second->set_pattern(pattern);
    }
}

SPDLOGC_API void spdlogc_set_logger_level(const char *logger_name,
                                          SPDLOGC_LEVEL level) {
    IF_NULL_RETURN(logger_name);
    if (auto logger = spdlog::get(logger_name)) {
        logger->set_level(static_cast<spdlog::level::level_enum>(level));
    }
}

SPDLOGC_API void spdlogc_create_basic_file_sink(const char *sink_name,
                                                const char *filename,
                                                SPDLOGC_BOOL truncate) {
    IF_NULL_RETURN(sink_name);
    IF_NULL_RETURN(filename);
    sinks_map[sink_name] = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        filename, __ToBool(truncate));
}

SPDLOGC_API void
spdlogc_create_rotating_file_sink(const char *sink_name, const char *filename,
                                  std::size_t max_size, std::size_t max_files,
                                  SPDLOGC_BOOL rotate_on_open) {
    IF_NULL_RETURN(sink_name);
    IF_NULL_RETURN(filename);
    sinks_map[sink_name] =
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            filename, max_size, max_files, __ToBool(rotate_on_open));
}

SPDLOGC_API void spdlogc_create_stdout_sink(const char *sink_name) {
    IF_NULL_RETURN(sink_name);
    sinks_map[sink_name] = std::make_shared<spdlog::sinks::stdout_sink_mt>();
}

SPDLOGC_API void spdlogc_append_sink_to_logger(const char *logger_name,
                                               const char *sink_name) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(sink_name);
    auto sink_it = sinks_map.find(sink_name);
    if (sink_it != sinks_map.end()) {
        if (auto logger = spdlog::get(logger_name)) {
            logger->sinks().push_back(sink_it->second);
        }
    }
}

SPDLOGC_API void spdlogc_remove_sink_from_logger(const char *logger_name,
                                                 const char *sink_name) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(sink_name);
    auto sink_it = sinks_map.find(sink_name);
    if (sink_it != sinks_map.end()) {
        if (auto logger = spdlog::get(logger_name)) {
            auto &sinks = logger->sinks();
            for (auto it = sinks.begin(); it != sinks.end(); it++) {
                if (*it == sink_it->second) {
                    sinks.erase(it);
                    break;
                }
            }
        }
    }
}

SPDLOGC_API void spdlogc_log(SPDLOGC_LEVEL level, const char *logger_name,
                             const char *fmt, ...) {
    IF_NULL_RETURN(logger_name);
    IF_NULL_RETURN(fmt);

    if (auto logger = spdlog::get(logger_name)) {
        char *buf = static_cast<char *>(__allocator(__buf_size));
        IF_NULL_RETURN(buf);
        memset(buf, __buf_size, 0x00);
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, __buf_size, fmt, args);
        va_end(args);
        logger->log(static_cast<spdlog::level::level_enum>(level), buf);
        __deleter(buf);
    }
}
