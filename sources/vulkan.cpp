#include "vulkan.h"

#include "exceptions.h"
#include "logging.h"


namespace vulkan {

    VulkanInstanceLifetimeManager::VulkanInstanceLifetimeManager(const std::shared_ptr<spdlog::logger> &logger) {
        this->logger = logger;
    }

    VkInstance& VulkanInstanceLifetimeManager::create() const {
        VkInstance ret;

        VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "vulkan_sandbox", 1,
            "vulkan_sandbox", 1, VK_MAKE_API_VERSION(1, 4, 309, 0)
        };

        const VkInstanceCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &applicationInfo, 0,
            nullptr, 0, nullptr
        };

        if (const auto result = vkCreateInstance(&createInfo, nullptr, &ret); result != VK_SUCCESS)
            throw exceptions::CriticalException{LOG_MESSAGE("vulkan", R"("failed to create instance")")};
        if (ret == nullptr)
            throw exceptions::CriticalException{LOG_MESSAGE("vulkan", R"("instance is nullptr")")};
        this->logger->info(LOG_MESSAGE("vulkan", R"("instance created")"));

        return ret;
    }

}
