#include "logging.h"
#include <vulkan/vulkan.h>

int main() {
    const auto logger = logging::create_logger();

    uint32_t extensionCount{};
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    logger->trace(LOG_MESSAGE("vulkan", std::format(R"("{} extensions available")", extensionCount)));

    logging::destroy_logger(logger);

    return 0;
}