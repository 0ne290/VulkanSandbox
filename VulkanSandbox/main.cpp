#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"

std::shared_ptr<spdlog::logger> CreateLogger()
{
    auto ret = spdlog::rotating_logger_mt<spdlog::async_factory>("async_file_logger",
        "async_log.txt", 1'073'741'824, 2);

    ret->set_pattern("[%P %t] %+");

    return ret;
}

void Configuring()
{

}

void Body(const std::shared_ptr<spdlog::logger> &logger)
{
    for (int i = 1; i <= 8000; i++) {
        logger->info("Zxc = {}", i);
    }
}

int main()
{
    const auto logger = CreateLogger();

    std::thread bodyThread(Body, logger);

    for (int i = 1; i <= 8000; i++) {
        logger->info("Cxz = {}", i);

    }

    bodyThread.join();

    spdlog::shutdown();

    return 0;
}