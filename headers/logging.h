#ifndef LOGGING_H

#define LOGGING_H
#define LOG_MESSAGE_WITHOUT_PAYLOAD(tag, desc) std::format(\
    R"({{"header":{{"tag":"{}","desc":"{}","source":"{}"}},"payload":null}})", \
    tag, \
    desc, \
    std::format("{} -> {} : {}", __FUNCTION__, __FILE__, __LINE__))
#define LOG_MESSAGE_WITH_PAYLOAD(tag, desc, payload) std::format(\
    R"({{"header":{{"tag":"{}","desc":"{}","source":"{}"}},"payload":{}}})", \
    tag, \
    desc, \
    std::format("{} -> {} : {}", __FUNCTION__, __FILE__, __LINE__), \
    payload)

#include <spdlog/logger.h>

namespace logging {

    class LoggerWrapper {

    public:

        // Constructors
        LoggerWrapper() = delete;

        explicit LoggerWrapper(const std::shared_ptr<spdlog::logger>&);

        // Copy constructors
        LoggerWrapper(const LoggerWrapper&) = delete;

        LoggerWrapper(LoggerWrapper&&) = delete;

        // Operators
        LoggerWrapper& operator=(const LoggerWrapper&) = delete;

        LoggerWrapper& operator=(LoggerWrapper&&) = delete;

        // Destructors
        ~LoggerWrapper();

        // Fields
        const std::shared_ptr<spdlog::logger> instance;

    };

    class LoggerCreator {

    public:

        // Constructors
        LoggerCreator() = delete;

        // Copy constructors
        LoggerCreator(const LoggerCreator&) = delete;

        LoggerCreator(LoggerCreator&&) = delete;

        // Operators
        LoggerCreator& operator=(const LoggerCreator&) = delete;

        LoggerCreator& operator=(LoggerCreator&&) = delete;

        // Destructors
        ~LoggerCreator() = delete;

        //Methods
        static std::shared_ptr<LoggerWrapper> create(spdlog::level::level_enum logLevel);

    };

}

#endif