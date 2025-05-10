#include "vulkan.h"

#include "exceptions.h"
#include "json.h"
#include "logging.h"

namespace vulkan {

    // VulkanFacadeCreator
    VulkanFacadeCreator::VulkanFacadeCreator(const std::shared_ptr<logging::LoggerWrapper> &logger) {
        this->logger = logger;
    }

    VkInstance createInstance();

    std::shared_ptr<VulkanFacade> VulkanFacadeCreator::create() const {
        // Prepare
        const auto instance = createInstance();

        // Construct
        const auto ret = std::make_shared<VulkanFacade>(instance, logger);
        this->logger->instance->info(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "facade created"));

        // Return
        return ret;
    }

    VkInstance createInstance() {
        VkInstance ret;

        constexpr VkApplicationInfo applicationInfo = {
            VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "vulkan_sandbox", 1,
            "vulkan_sandbox", 1, VK_MAKE_API_VERSION(1, 4, 309, 0)
        };

        const VkInstanceCreateInfo createInfo = {
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &applicationInfo, 0,
            nullptr, 0, nullptr
        };

        const auto result = vkCreateInstance(&createInfo, nullptr, &ret);
        if (result != VK_SUCCESS)
            throw exceptions::CriticalException{LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "failed to create instance")};

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

    void VulkanFacade::logPhysicalDevices() const {
        // Get physical devices
        uint32_t physicalDeviceCount;
        auto result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
        if (result != VK_SUCCESS) {
            logger->instance->warn(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "failed to get physical device count"));
        }

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
        if (result != VK_SUCCESS) {
            logger->instance->warn(LOG_MESSAGE_WITHOUT_PAYLOAD("vulkan", "failed to get physical devices"));
        }

        static void (*getProperties)(const VkPhysicalDevice&, VkPhysicalDeviceProperties&) =
            [](const VkPhysicalDevice &device, VkPhysicalDeviceProperties &properties) {
                vkGetPhysicalDeviceProperties(device, &properties);
            };
        const auto devicesJson = json::JsonSerializer::toJson(physicalDevices, getProperties);
        logger->instance->trace(LOG_MESSAGE_WITH_PAYLOAD("vulkan", "physical devices", devicesJson));
    }

}
