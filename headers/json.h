#ifndef JSON_H

#define JSON_H

#include <string>

namespace json {
    std::string to_json();
    void from_json(std::string json);
}

#endif
