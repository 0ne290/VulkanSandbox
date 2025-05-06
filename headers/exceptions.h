#ifndef EXCEPTIONS_H

#define EXCEPTIONS_H
#include <string>

namespace exceptions {

    class CriticalException {

    public:

        // Constructors
        CriticalException() = delete;

        explicit CriticalException(const std::string &message);

        // Copy constructors
        CriticalException(const CriticalException&) = delete;

        CriticalException(CriticalException&&) = delete;

        // Operators
        CriticalException& operator=(const CriticalException&) = delete;

        CriticalException& operator=(CriticalException&&) = delete;

        // Destructors
        //~CriticalException() = delete;

        // Methods
        std::string getMessage() const;

    private:

        // Fields
        std::string message;

    };

}

#endif