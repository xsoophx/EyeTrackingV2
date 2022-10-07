#include "Exceptions.hpp"

BaseException::BaseException(QString const &message)
    : BaseException{message.toStdString()}
{}
