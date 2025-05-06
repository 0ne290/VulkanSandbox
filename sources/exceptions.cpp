#include "exceptions.h"

namespace exceptions {

    CriticalException::CriticalException(const std::string &message) {
        this->message = message.c_str();
    }

    const char* CriticalException::what() const {
        return message;
    }

}