#ifndef __SPDLOGC_H__
#define __SPDLOGC_H__

#define SPDLOG_CAPI extern "C"

SPDLOG_CAPI void spdlog_set_pattern(const char *pattern);
SPDLOG_CAPI void spdlog_regist_logger(const char *logger, const char *logger_type);
SPDLOG_CAPI void spdlog_trace(const char *logger, const char *fmt, ...);
SPDLOG_CAPI void spdlog_debug(const char *logger, const char *fmt, ...);
SPDLOG_CAPI void spdlog_info(const char *logger, const char *fmt, ...);
SPDLOG_CAPI void spdlog_warn(const char *logger, const char *fmt, ...);
SPDLOG_CAPI void spdlog_error(const char *logger, const char *fmt, ...);
SPDLOG_CAPI void spdlog_critical(const char *logger, const char *fmt, ...);

#endif // __SPDLOGC_H__