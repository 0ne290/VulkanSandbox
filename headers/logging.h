#ifndef LOGGING_H

#define LOGGING_H
#define LOG_MESSAGE(tag, payload) std::format(R"({{"header":{{"tag":"{}","source":"{}"}},"payload":{}}})", tag, \
    std::format("{} -> {} : {}", __FUNCTION__, __FILE__, __LINE__), payload)

#include <spdlog/logger.h>

namespace logging {

    class LoggerLifetimeManager {

    public:

        // Constructors
        LoggerLifetimeManager() = delete;

        // Copy constructors
        LoggerLifetimeManager(const LoggerLifetimeManager&) = delete;

        LoggerLifetimeManager(LoggerLifetimeManager&&) = delete;

        // Operators
        LoggerLifetimeManager& operator=(const LoggerLifetimeManager&) = delete;

        LoggerLifetimeManager& operator=(LoggerLifetimeManager&&) = delete;

        // Destructors
        ~LoggerLifetimeManager() = delete;

        //Methods
        static std::shared_ptr<spdlog::logger> create(spdlog::level::level_enum logLevel);

        static void destroy(const std::shared_ptr<spdlog::logger> &logger);

    };

}

#endif