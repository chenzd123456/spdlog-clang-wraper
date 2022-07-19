#include "common.h"

#if 1
#include <spdlogc/spdlogc.h>

TEST(spdlogc_test, spdlogc_append_stdout_sink_to_logger) {
    spdlogc_init_thread_pool(100, 1);
    spdlogc_create_async_logger("spdlogc_test");
    spdlogc_set_level("spdlogc_test", SPDLOG_LEVEL_DEBUG);
    spdlogc_set_pattern("spdlogc_test",
                        "[%Y-%m-%d %H:%M:%S.%e] [%6P:%6t] [%l] [%n] %v");
    spdlogc_append_stdout_sink_to_logger("spdlogc_test");
    spdlogc_append_basic_file_sink_to_logger("spdlogc_test", "test.log");
    SPDLOGC_DEBUG("spdlogc_test", "hello world %s %d", "eco", 10);
}
#endif