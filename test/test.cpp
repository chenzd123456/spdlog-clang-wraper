#include <spdlogc/spdlogc.h>
#include "common.h"

#include <iostream>

TEST(spdlogc_test, spdlogc_append_stdout_sink_to_logger) {
    spdlogc_set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%6P:%6t] [%l] [%n] %v");
    spdlogc_set_level("spdlogc_test", 0);
    spdlogc_append_stdout_sink_to_logger("spdlogc_test");
    spdlogc_append_basic_file_sink_to_logger("spdlogc_test", "test.log");
    spdlogc_log_debug("spdlogc_test", "hello world %s %d", "eco", 10);
}