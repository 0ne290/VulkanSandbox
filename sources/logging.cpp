#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "logging.h"

namespace logging {

    std::shared_ptr<LoggerWrapper> LoggerCreator::create(const spdlog::level::level_enum logLevel) {
        const auto logger = spdlog::rotating_logger_mt<spdlog::async_factory>("logger", "log.json",
            1'073'741'824, 2);
        logger->set_level(logLevel);
        const auto spdlog_tp = spdlog::thread_pool();

        logger->set_pattern(R"({"log":[)");
        logger->info("");
        logger->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        logger->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v},)");
        logger->info(LOG_MESSAGE_WITHOUT_PAYLOAD("logger", "wrapper created"));
        logger->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        return std::make_shared<LoggerWrapper>(logger);
    }

    LoggerWrapper::LoggerWrapper(const std::shared_ptr<spdlog::logger> &logger) : instance(logger) { }

    LoggerWrapper::~LoggerWrapper() {
        const auto spdlog_tp = spdlog::thread_pool();

        instance->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        instance->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v})");
        instance->info(LOG_MESSAGE_WITHOUT_PAYLOAD("logger", "wrapper destroyed"));
        instance->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        instance->set_pattern("]}");
        instance->info("");

        spdlog::shutdown();
    }

}
