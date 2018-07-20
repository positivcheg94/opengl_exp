#pragma once

#include<type_traits>

namespace ogl
{
    namespace utils
    {
        template <typename E>
        constexpr inline typename std::underlying_type<E>::type to_underlying(E e) noexcept {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }
    }

    enum class Bool : GLboolean
    {
        True    = GL_TRUE,
        False   = GL_FALSE
    };
}