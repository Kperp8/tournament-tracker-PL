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

class TeamNotFound : public std::exception
{
    std::string message;
public:
    explicit TeamNotFound(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class SameTeamGame : public std::exception
{
    std::string message;
public:
    explicit SameTeamGame(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class WrongFilePath : public std::exception
{
    std::string message;
public:
    explicit WrongFilePath(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ReadFileError : public std::exception
{
    std::string message;
public:
    explicit ReadFileError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class WriteFileError : public std::exception
{
    std::string message;
public:
    explicit WriteFileError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class NoAdvTeam : public std::exception
{
    std::string message;
public:
    explicit NoAdvTeam(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_H
