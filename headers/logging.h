#ifndef LOGGING_H

#define LOGGING_H
#define LOG_MESSAGE(tag, payload) R"({{"header":{{"tag":"{}","source":"{}"}},"payload":{}}})", tag, \
    std::format("{} -> {} : {}", __FUNCTION__, __FILE__, __LINE__), payload

#include <spdlog/logger.h>

namespace logging {
    std::shared_ptr<spdlog::logger> create_logger();

    void destroy_logger(const std::shared_ptr<spdlog::logger> &logger);
}

#endif