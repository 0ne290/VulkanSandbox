#include "vulkan.h"

#include <iostream>

#include "exceptions.h"
#include "json.h"
#include "logging.h"


namespace vulkan {

    // VulkanFacadeCreator
    VulkanFacadeCreator::VulkanFacadeCreator(const std::shared_ptr<logging::LoggerWrapper> &logger) {
        this->logger = logger;
    }

    std::unique_ptr<VulkanFacade> VulkanFacadeCreator::create() const {
        // Create instance
        VkInstance instance;

        VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "vulkan_sandbox", 1,
            "vulkan_sandbox", 1, VK_MAKE_API_VERSION(1, 4, 309, 0)
        };

        const VkInstanceCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &applicationInfo, 0,
            nullptr, 0, nullptr
        };

        auto result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
            throw exceptions::CriticalException{LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan",
                json::JsonSerializer::toJson("failed to create instance"))};
        std::unique_ptr<VulkanFacade> ret(new VulkanFacade(instance, logger));
        this->logger->instance->info(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "facade created"));

        // Get physical devices
        uint32_t physicalDeviceCount;
        result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
        if (result != VK_SUCCESS) {
            logger->instance->warn(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "failed to get physical device count"));

            return ret;
        }

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
        if (result != VK_SUCCESS) {
            logger->instance->warn(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "failed to get physical devices"));

            return ret;
        }
        this->logger->instance->trace(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan",
            std::format("got {} physical devices", physicalDeviceCount)));

        // Get physical devices properties
        VkPhysicalDeviceProperties physicalDeviceProperties;
        std::vector<VkPhysicalDeviceProperties> physicalDevicesProperties(physicalDeviceCount);
        for (auto i = 0; i < physicalDevices.size(); i++) {
            vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);

            physicalDevicesProperties[i] = physicalDeviceProperties;
        }
        this->logger->instance->trace(LOG_MESSAGE_WITH_PAYLOAD("vulkan", "got physical devices properties", json::JsonSerializer::toJson(physicalDevicesProperties)));

        // Get physical devices features

        // Get extensions

        // Get layers

        return ret;
    }

    // VulkanFacade
    VulkanFacade::VulkanFacade(const VkInstance &instance, const std::shared_ptr<logging::LoggerWrapper> &logger) {
        this->instance = instance;
        this->logger = logger;
    }

    VulkanFacade::~VulkanFacade() {
        vkDestroyInstance(this->instance, nullptr);
        this->logger->instance->info(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "facade destroyed"));
    }

}
