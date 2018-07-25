#pragma once

#include<memory>
#include<vector>
#include<set>

// forward declaration hpp
#include<ogl/ogl_forward.hpp>
#include <ogl/types.hpp>
#include <ogl/buffers/buffer.hpp>

namespace ogl
{
    struct VerticeAttribute
    {
        std::uint16_t   index;
        std::uint16_t   cols;
        Bool            normalized;
        std::uint16_t   stride;
        std::uint16_t   offset;
    };

    struct BufferLayout
    {
        typedef typename Buffer::pointer_type   buffer_type;
        typedef std::vector<VerticeAttribute>   layout_type;

        BufferLayout(buffer_type buffer, layout_type layout) :
            buffer(std::move(buffer)), layout(std::move(layout))
        {

        }

        BufferLayout(const BufferLayout&)   = default;
        BufferLayout(BufferLayout&&)        = default;

        buffer_type buffer;
        layout_type layout;
    };

    class ArrayBuffer
    {
    public:
        typedef typename Buffer::pointer_type           buffer_type;
        typedef typename std::shared_ptr<ArrayBuffer>   pointer_type;
    protected:
        ArrayBuffer(std::vector<BufferLayout> buffers, buffer_type indexer) :
            buffers(std::move(buffers)), indexer(std::move(indexer))
        {
            std::set<size_t> used;
            glGenVertexArrays(1, &id);
            glBindVertexArray(id);
            for (auto& bl : this->buffers)
            {
                auto& b = bl.buffer;
                b->activate();
                for (auto& l : bl.layout)
                {
                    auto insert_result = used.insert(l.index);
                    if (!insert_result.second)
                    {
                        b->deactivate();
                        glBindVertexArray(0);
                        throw std::runtime_error("Index is used already");
                    }
                    glVertexAttribPointer(l.index, l.cols, b->get_value_type().type_index, utils::to_underlying(l.normalized), b->get_value_type().type_size * l.stride, reinterpret_cast<void*>(b->get_value_type().type_size * l.offset));
                    glEnableVertexAttribArray(l.index);
                }
                b->deactivate();
            }
            if (this->indexer)
                this->indexer->activate();
            glBindVertexArray(0);
        }

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&&) = delete;

    public:
        static pointer_type create(std::vector<BufferLayout> buffers, buffer_type index_buffer)
        {
            return pointer_type{ new ArrayBuffer{ std::move(buffers), std::move(index_buffer) } };
        }

        void activate()
        {
            glBindVertexArray(id);
        }

        void deactivate()
        {
            glBindVertexArray(0);
        }

        ~ArrayBuffer()
        {
            glDeleteVertexArrays(1, &id);
        }

    protected:
        // members
        GLuint id;

        std::vector<BufferLayout>   buffers;
        buffer_type                 indexer;
    };
}