#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"

std::shared_ptr<spdlog::logger> CreateLogger() {
    auto ret = spdlog::rotating_logger_mt<spdlog::async_factory>("logger", "log.json",
        1'073'741'824, 2);
    const auto spdlog_tp = spdlog::thread_pool();

    ret->set_pattern(R"({"log":[)");
    ret->info("");
    ret->flush();
    while (spdlog_tp->queue_size() != 0)
        std::this_thread::yield();

    ret->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v},)");
    ret->info(R"("Logger created.")");
    ret->flush();
    while (spdlog_tp->queue_size() != 0)
        std::this_thread::yield();

    return ret;
}

void DestroyLogger(const std::shared_ptr<spdlog::logger> &logger) {
    const auto spdlog_tp = spdlog::thread_pool();

    logger->set_pattern(R"({"time":"%Y-%m-%d %H:%M:%S.%e","level":"%l","process":%P,"thread":%t,"message":%v})");
    logger->info(R"("Logger destroyed.")");
    logger->flush();
    while (spdlog_tp->queue_size() != 0)
        std::this_thread::yield();

    logger->set_pattern("]}");
    logger->info("");

    spdlog::shutdown();
}

void Configuring()
{

}

void Body(const std::shared_ptr<spdlog::logger> &logger)
{
    for (auto i = 0; i < 10; i++) {
        logger->info(R"("Zxc = {}")", i);
    }
}

int main()
{
    const auto logger = CreateLogger();

    std::thread bodyThread(Body, logger);

    for (auto i = 0; i < 10; i++) {
        logger->info(R"("Cxz = {}")", i);
    }

    bodyThread.join();

    DestroyLogger(logger);

    return 0;
}