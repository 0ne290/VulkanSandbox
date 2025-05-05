#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "logging.h"

namespace logging {
    std::shared_ptr<spdlog::logger> create_logger() {
        auto ret = spdlog::rotating_logger_mt<spdlog::async_factory>("logger", "log.json",
            1'073'741'824, 2);
        ret->set_level(spdlog::level::trace);
        const auto spdlog_tp = spdlog::thread_pool();

        ret->set_pattern(R"({"log":[)");
        ret->info("");
        ret->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        ret->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v},)");
        ret->info(LOG_MESSAGE("logger", R"("created")"));
        ret->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        return ret;
    }

    void destroy_logger(const std::shared_ptr<spdlog::logger> &logger) {
        const auto spdlog_tp = spdlog::thread_pool();

        logger->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        logger->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v})");
        logger->info(LOG_MESSAGE("logger", R"("destroyed")"));
        logger->flush();
        while (spdlog_tp->queue_size() != 0)
            std::this_thread::yield();

        logger->set_pattern("]}");
        logger->info("");

        spdlog::shutdown();
    }
}