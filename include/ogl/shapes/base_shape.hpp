#pragma once

namespace ogl
{

    class base_shape
    {
        virtual std::vector<float> generate_triangles() = 0;
    };
}