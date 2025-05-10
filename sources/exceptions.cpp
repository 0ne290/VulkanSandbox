#include "exceptions.h"

namespace exceptions {

    CriticalException::CriticalException(std::string message) : message(std::move(message)) { }

    const char* CriticalException::what() const noexcept {
        return message.c_str();
    }

}
