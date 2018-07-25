#pragma once

#include<type_traits>

namespace ogl
{
    enum class Bool : GLboolean
    {
        True    = GL_TRUE,
        False   = GL_FALSE
    };
    
    constexpr Bool True     = Bool::True;
    constexpr Bool False    = Bool::False;

    struct ValueType
    {
        GLenum type_index;
        size_t type_size;
    };

    constexpr ValueType Float   { GL_FLOAT          , sizeof(float)         };
    constexpr ValueType UInt    { GL_UNSIGNED_INT   , sizeof(unsigned int)  };

    namespace utils
    {
        template <typename E>
        constexpr inline typename std::underlying_type<E>::type to_underlying(E e) noexcept {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }
    }

    enum class BufferType : GLenum
    {
        Array = GL_ARRAY_BUFFER,
        ElementArray = GL_ELEMENT_ARRAY_BUFFER,
        CopyRead = GL_COPY_READ_BUFFER,
        CopyWrite = GL_COPY_WRITE_BUFFER,
        PixelUnpack = GL_PIXEL_UNPACK_BUFFER,
        PixelPack = GL_PIXEL_PACK_BUFFER,
        Texture = GL_TEXTURE_BUFFER,
        TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
        Uniform = GL_UNIFORM_BUFFER
    };

    enum class UsageHint : GLenum
    {
        StaticDraw = GL_STATIC_DRAW,
        StaticCopy = GL_STATIC_COPY,
        StaticRead = GL_STATIC_READ,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicCopy = GL_DYNAMIC_COPY,
        DynamicRead = GL_DYNAMIC_READ,
        StreamDraw = GL_STREAM_DRAW,
        StreamCopy = GL_STREAM_COPY,
        StreamRead = GL_STREAM_READ
    };

    enum class ShaderType : GLenum
    {
        Vertex      = GL_VERTEX_SHADER,
        Fragment    = GL_FRAGMENT_SHADER
    };
}