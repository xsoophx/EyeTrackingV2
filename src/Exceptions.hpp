#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

#include <QtCore/QString>

struct BaseException: std::runtime_error
{
    using std::runtime_error::runtime_error;
    using std::runtime_error::operator=;

    explicit BaseException(QString const &message);
};


#endif //EXCEPTIONS_HPP
