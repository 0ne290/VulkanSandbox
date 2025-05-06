#include "vulkan.h"

#include "exceptions.h"
#include "logging.h"


namespace vulkan {

    VulkanInstanceLifetimeManager::VulkanInstanceLifetimeManager(const std::shared_ptr<spdlog::logger> &logger) {
        this->logger = logger;
    }

    VkInstance& VulkanInstanceLifetimeManager::create() const {
        // Create instance
        VkInstance ret;

        VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "vulkan_sandbox", 1,
            "vulkan_sandbox", 1, VK_MAKE_API_VERSION(1, 4, 309, 0)
        };

        const VkInstanceCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &applicationInfo, 0,
            nullptr, 0, nullptr
        };

        auto result = vkCreateInstance(&createInfo, nullptr, &ret);
        if (result != VK_SUCCESS)
            throw exceptions::CriticalException{LOG_MESSAGE("vulkan", R"("failed to create instance")")};
        this->logger->info(LOG_MESSAGE("vulkan", R"("instance created")"));

        // Get physical devices
        uint32_t physicalDeviceCount;
        result = vkEnumeratePhysicalDevices(ret, &physicalDeviceCount, nullptr);
        if (result != VK_SUCCESS) {
            logger->warn(LOG_MESSAGE("vulkan", R"("failed to get physical device count")"));

            return ret;
        }

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        result = vkEnumeratePhysicalDevices(ret, &physicalDeviceCount, physicalDevices.data());
        if (result != VK_SUCCESS) {
            logger->warn(LOG_MESSAGE("vulkan", R"("failed to get physical devices")"));

            return ret;
        }

        // Get physical devices properties
        VkPhysicalDeviceProperties physicalDeviceProperties;
        for (const auto& physicalDevice : physicalDevices) {
            vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
        }

        // Get physical devices features

        // Get extensions

        // Get layers

        return ret;
    }

    void VulkanInstanceLifetimeManager::destroy(const VkInstance &vulkanInstance) const {
        vkDestroyInstance(vulkanInstance, nullptr);
        this->logger->info(LOG_MESSAGE("vulkan", R"("instance destroyed")"));
    }

}
