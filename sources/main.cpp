#include "logging.h"
#include <vulkan/vulkan.h>

int main() {
    const auto logger = logging::LoggerLifetimeManager::create(spdlog::level::trace);

    uint32_t extensionCount{};
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    logger->trace(LOG_MESSAGE("vulkan", std::format(R"("{} extensions available")", extensionCount)));

    logging::LoggerLifetimeManager::destroy(logger);

    return 0;
}