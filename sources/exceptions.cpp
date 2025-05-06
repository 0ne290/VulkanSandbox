#include <string>
#include "exceptions.h"

namespace exceptions {

    CriticalException::CriticalException(const std::string &message) {
        this->message = message;
    }

    std::string CriticalException::getMessage() const {
        return message;
    }

}