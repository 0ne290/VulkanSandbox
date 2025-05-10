#ifndef EXCEPTIONS_H

#define EXCEPTIONS_H
#include <string>

namespace exceptions {

    class CriticalException final : public std::exception {

    public:

        // Constructors
        CriticalException() = delete;

        explicit CriticalException(std::string message);

        // Copy constructors
        CriticalException(const CriticalException&) = delete;

        CriticalException(CriticalException&&) = delete;

        // Operators
        CriticalException& operator=(const CriticalException&) = delete;

        CriticalException& operator=(CriticalException&&) = delete;

        // Destructors
        //~CriticalException() override = delete;

        // Methods
        [[nodiscard]] const char* what() const noexcept override;

    private:

        // Fields
        const std::string message;

    };

}

#endif