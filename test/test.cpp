#include "common.h"

#if 1
#include <spdlogc/spdlogc.h>

TEST(spdlogc_test, spdlogc_append_stdout_sink_to_logger) {
    const char *pattern = "[%H:%M:%S %z] [thread %t] [%l] [%n] %v";
    const char *logger1 = "spdlogc_test1";
    const char *logger2 = "spdlogc_test2";
    const char *file_sink = "fileout";
    const char *console_sink = "stdout";

    spdlogc_init_thread_pool(10, 1);

    spdlogc_create_rotating_file_sink(file_sink, "test.log", 1024, 3);
    spdlogc_set_sink_pattern(file_sink, pattern);

    spdlogc_create_stdout_sink(console_sink);
    spdlogc_set_sink_pattern(console_sink, pattern);

    spdlogc_create_async_logger(logger1);
    spdlogc_set_logger_level(logger1, SPDLOGC_LEVEL_TRACE);
    spdlogc_append_sink_to_logger(logger1, file_sink);
    spdlogc_append_sink_to_logger(logger1, console_sink);

    spdlogc_create_async_logger(logger2);
    spdlogc_set_logger_level(logger2, SPDLOGC_LEVEL_TRACE);
    spdlogc_append_sink_to_logger(logger2, file_sink);
    spdlogc_append_sink_to_logger(logger2, console_sink);

    SPDLOGC_TRACE(logger1, "hello world1 %s %d", "eco", 10);
    SPDLOGC_DEBUG(logger1, "hello world2 %s %d", "eco", 10);
    SPDLOGC_INFO(logger1, "hello world3 %s %d", "eco", 10);
    SPDLOGC_WARNNING(logger1, "hello world4 %s %d", "eco", 10);
    SPDLOGC_ERROR(logger1, "hello world5 %s %d", "eco", 10);
    SPDLOGC_CRITICAL(logger1, "hello world6 %s %d", "eco", 10);
    SPDLOGC_TRACE(logger2, "hello world1 %s %d", "eco", 10);
    SPDLOGC_DEBUG(logger2, "hello world2 %s %d", "eco", 10);
    SPDLOGC_INFO(logger2, "hello world3 %s %d", "eco", 10);
    SPDLOGC_WARNNING(logger2, "hello world4 %s %d", "eco", 10);
    SPDLOGC_ERROR(logger2, "hello world5 %s %d", "eco", 10);
    SPDLOGC_CRITICAL(logger2, "hello world6 %s %d", "eco", 10);
}
#endif