#pragma once

#include<memory>

// forward declaration hpp
#include<ogl/ogl_forward.hpp>
#include<ogl/types.hpp>

namespace ogl
{
    class Buffer
    {
        friend class ArrayBuffer;
    protected:
        Buffer(BufferType buffer_type, ValueType value_type, const void* ptr, size_t size, UsageHint usage_hint) :
            buffer_type(buffer_type), id(0), value_type(value_type), buffer_size(size), usage_hint(usage_hint)
        {
            glGenBuffers(1, &id);

            load_data(ptr, size, usage_hint);
        }

        void load_data(const void* ptr, size_t size, UsageHint usage_hint)
        {
            glBindBuffer(utils::to_underlying(buffer_type), id);
            glBufferData(utils::to_underlying(buffer_type), size, ptr, utils::to_underlying(usage_hint));
            glBindBuffer(utils::to_underlying(buffer_type), 0);
        }

        Buffer(const Buffer&) = delete;
        Buffer(Buffer&&) = delete;

    public:
        typedef std::shared_ptr<Buffer> pointer_type;

        static pointer_type create(BufferType buffer_type, ValueType value_type, const void* ptr, size_t size, UsageHint usage_hint)
        {
            return pointer_type{ new Buffer{ buffer_type, value_type, ptr, size, usage_hint } };
        }

        void activate()
        {
            glBindBuffer(utils::to_underlying(buffer_type), id);
        }

        void deactivate()
        {
            glBindBuffer(utils::to_underlying(buffer_type), 0);
        }

        ValueType get_value_type() const
        {
            return value_type;
        }

        ~Buffer()
        {
            glDeleteBuffers(1, &id);
        }

    protected:
        // members
        BufferType  buffer_type;
        GLuint      id;
        ValueType   value_type;
        size_t      buffer_size;
        UsageHint   usage_hint;
    };
}