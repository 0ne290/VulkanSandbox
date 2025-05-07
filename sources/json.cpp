#include "json.h"

#include <format>
#include <vector>

namespace json {

    std::string JsonSerializer::toJson(const std::string &text) {
        return std::format(R"("{}")", text);
    }

    std::string JsonSerializer::toJson(const std::vector<VkPhysicalDeviceProperties> &devicesProperties) {
        std::string ret("[");

        for (auto i = 0; i < devicesProperties.size() - 1; i++) {
            auto properties = devicesProperties[i];
            ret.append(std::format(
                R"({{"apiVersion":{},"driverVersion":{},"vendorId":{},"deviceId":{},"deviceType":"stub","deviceName":{}}},)",
                properties.apiVersion,
                properties.driverVersion,
                properties.vendorID,
                properties.deviceID,
                //properties.deviceType,
                properties.deviceName
                ));
        }

        auto properties = devicesProperties[devicesProperties.size() - 1];
        ret.append(std::format(
            R"({{"apiVersion":{},"driverVersion":{},"vendorId":{},"deviceId":{},"deviceType":"stub","deviceName":{}}})",
            properties.apiVersion,
            properties.driverVersion,
            properties.vendorID,
            properties.deviceID,
            //properties.deviceType,
            properties.deviceName
            ));

        ret.append("]");

        return ret;
    }

}
