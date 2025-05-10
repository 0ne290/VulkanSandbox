#ifndef VULKAN_H

#define VULKAN_H
#include <spdlog/logger.h>
#include <vulkan/vulkan_core.h>

#include "logging.h"

namespace vulkan {
    class VulkanFacade;

    class VulkanFacadeCreator {

    public:

        // Constructors
        VulkanFacadeCreator() = delete;

        explicit VulkanFacadeCreator(const std::shared_ptr<logging::LoggerWrapper> &);

        // Copy constructors
        VulkanFacadeCreator(const VulkanFacadeCreator&) = delete;

        VulkanFacadeCreator(VulkanFacadeCreator&&) = delete;

        // Operators
        VulkanFacadeCreator& operator=(const VulkanFacadeCreator&) = delete;

        VulkanFacadeCreator& operator=(VulkanFacadeCreator&&) = delete;

        // Destructors
        //~VulkanFacadeCreator() = delete;

        // Methods
        [[nodiscard]] std::shared_ptr<VulkanFacade> create() const;

    private:

        // Fields
        std::shared_ptr<logging::LoggerWrapper> logger;

    };

    class VulkanFacade {

    public:

        // Constructors
        VulkanFacade() = delete;

        VulkanFacade(const VkInstance &, const std::shared_ptr<logging::LoggerWrapper> &);

        // Copy constructors
        VulkanFacade(const VulkanFacade&) = delete;

        VulkanFacade(VulkanFacade&&) = delete;

        // Operators
        VulkanFacade& operator=(const VulkanFacade&) = delete;

        VulkanFacade& operator=(VulkanFacade&&) = delete;

        // Destructors
        ~VulkanFacade();

        // Methods
        void logPhysicalDevices() const;

        void logExtensions() const;

        void logLayers() const;

    private:

        // Fields
        VkInstance instance;

        std::shared_ptr<logging::LoggerWrapper> logger;

    };

}

#endif