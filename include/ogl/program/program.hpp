#pragma once

#include<ogl/program/shader.hpp>

namespace ogl
{
    class Program
    {
    protected:
        typedef typename Shader::pointer_type shader;

        Program(shader vertex, shader fragment, bool delete_after = true) :
            id(glCreateProgram()), vertex(std::move(vertex)), fragment(std::move(fragment))
        {
            if (this->vertex->get_type() != ShaderType::Vertex || this->fragment->get_type() != ShaderType::Fragment)
                throw std::runtime_error("Shaders must be vertex and fragment");

            glAttachShader(id, this->vertex->id   );
            glAttachShader(id, this->fragment->id );

            glLinkProgram(id);

            if (delete_after)
            {
                this->vertex.reset();
                this->fragment.reset();
            }
        }

    public:
        typedef std::shared_ptr<Program> pointer_type;

        template<typename ... Args>
        static pointer_type create(Args&& ... args)
        {
            return pointer_type{ new Program(std::forward<Args>(args)...) };
        }

        void activate()
        {
            glUseProgram(id);
        }

        void deactivate()
        {
            glUseProgram(0);
        }

        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(id, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(id, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void setVec2(const std::string &name, const glm::vec2 &value) const
        {
            glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec2(const std::string &name, float x, float y) const
        {
            glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value) const
        {
            glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec3(const std::string &name, float x, float y, float z) const
        {
            glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value) const
        {
            glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
        }
        void setVec4(const std::string &name, float x, float y, float z, float w) const
        {
            glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        ~Program()
        {
            glDeleteProgram(id);
        }

    protected:
        GLuint id;

        shader vertex;
        shader fragment;
    };
}