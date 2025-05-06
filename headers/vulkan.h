#ifndef VULKAN_H

#define VULKAN_H
#include <spdlog/logger.h>
#include <vulkan/vulkan_core.h>

namespace vulkan {

    class VulkanInstanceLifetimeManager {

    public:

        // Constructors
        VulkanInstanceLifetimeManager() = delete;

        VulkanInstanceLifetimeManager(const std::shared_ptr<spdlog::logger> &);

        // Copy constructors
        VulkanInstanceLifetimeManager(const VulkanInstanceLifetimeManager&) = delete;

        VulkanInstanceLifetimeManager(VulkanInstanceLifetimeManager&&) = delete;

        // Operators
        VulkanInstanceLifetimeManager& operator=(const VulkanInstanceLifetimeManager&) = delete;

        VulkanInstanceLifetimeManager& operator=(VulkanInstanceLifetimeManager&&) = delete;

        // Destructors
        ~VulkanInstanceLifetimeManager() = delete;

        // Methods
        VkInstance& create() const;

        void destroy(VkInstance&);

    private:

        // Fields
        std::shared_ptr<spdlog::logger> logger;

    };

}

#endif