#include "exceptions.h"
#include "logging.h"
#include "vulkan.h"

int main() {
    const auto logger = logging::LoggerCreator::create(spdlog::level::trace);

    try {
        const auto vulkanFacadeCreator = vulkan::VulkanFacadeCreator(logger);

        const auto vulkanFacade = vulkanFacadeCreator.create();
        vulkanFacade->logPhysicalDevices();

        return 0;
    } catch (const exceptions::CriticalException &ex) {
        logger->instance->critical(ex.what());

        return 1;
    }
}
