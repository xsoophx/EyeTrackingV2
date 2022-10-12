#ifndef CONFIG_EXCEPTION_HPP
#define CONFIG_EXCEPTION_HPP

#include "../Exceptions.hpp"

namespace config
{
struct LoadingException final: BaseException
{
    using BaseException::BaseException;
    using BaseException::operator=;
};
}

#endif // CONFIG_EXCEPTION_HPP
