#ifndef JSON_H

#define JSON_H

#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace json {

    class JsonSerializer {

    public:

        // Constructors
        JsonSerializer() = delete;

        // Copy constructors
        JsonSerializer(const JsonSerializer&) = delete;

        JsonSerializer(JsonSerializer&&) = delete;

        // Operators
        JsonSerializer& operator=(const JsonSerializer&) = delete;

        JsonSerializer& operator=(JsonSerializer&&) = delete;

        // Destructors
        ~JsonSerializer() = delete;

        // Methods
        static std::string toJson(const std::string&);

        static std::string toJson(const std::vector<VkPhysicalDeviceProperties>&);

    };

}

#endif
