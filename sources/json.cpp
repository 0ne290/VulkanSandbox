#include "json.h"

#include <format>
#include <vector>

namespace json {

    std::string JsonSerializer::toJson(const std::string &text) {
        return std::format(R"("{}")", text);
    }

    std::string toString(const VkPhysicalDeviceType deviceType) {
        static const std::string stringsByDeviceType[5] = {
            "OTHER", "INTEGRATED_GPU", "DISCRETE_GPU", "VIRTUAL_GPU", "CPU"
        };

        return stringsByDeviceType[deviceType];
    }

    // ReSharper disable once CppDFAConstantFunctionResult
    std::string JsonSerializer::toJson(const std::vector<VkPhysicalDevice> &devices, void
        (*& getProperties)(const VkPhysicalDevice&, VkPhysicalDeviceProperties&)) {
        VkPhysicalDeviceProperties properties;
        std::string ret("[");

        for (auto i = 0; i < devices.size() - 1; i++) {
            getProperties(devices[i], properties);
            ret.append(std::format(
                R"({{"apiVersion":{},"driverVersion":{},"vendorId":{},"deviceId":{},"deviceType":"{}","deviceName":"{}"}},)",
                properties.apiVersion,
                properties.driverVersion,
                properties.vendorID,
                properties.deviceID,
                toString(properties.deviceType),
                properties.deviceName
                ));
        }

        getProperties(devices[devices.size() - 1], properties);
        ret.append(std::format(
            R"({{"apiVersion":{},"driverVersion":{},"vendorId":{},"deviceId":{},"deviceType":"{}","deviceName":"{}"}})",
            properties.apiVersion,
            properties.driverVersion,
            properties.vendorID,
            properties.deviceID,
            toString(properties.deviceType),
            properties.deviceName
            ));

        ret.append("]");

        return ret;
    }

}
