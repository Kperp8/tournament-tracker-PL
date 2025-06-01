#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

// plik na klasy wyjątków
class NoTeamName : public std::exception
{
    std::string message;
public:
    explicit NoTeamName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class WrongTeamName : public std::exception
{
    std::string message;
public:
    explicit WrongTeamName(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_H
