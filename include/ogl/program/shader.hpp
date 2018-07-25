#pragma once

#include<fstream>
#include<filesystem>

// forward declaration hpp
#include<ogl/ogl_forward.hpp>
#include<ogl/types.hpp>

namespace ogl
{
    class Shader
    {
        friend class Program;
    protected:
        static std::string read_file(const std::filesystem::path& path)
        {
            std::ifstream stream{ path };
            return std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
        }

        Shader(ShaderType type, const std::filesystem::path& path, bool keep_code)
            : Shader(type, read_file(path), keep_code)
        {

        }

        Shader(ShaderType type, const std::string& code, bool keep_code) :
            id(glCreateShader(utils::to_underlying(type))),
            type(type), code(std::move(code))
        {
            auto code_cstr = this->code.c_str();
            glShaderSource(id, 1, &code_cstr, nullptr);
            if (!keep_code)
                this->code.clear();
            glCompileShader(id);

            int compile_status = 0;
            glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
            if (!compile_status)
            {
                glDeleteShader(id);
                throw std::runtime_error("Shader compilation failed");
            }
        }

    public:
        typedef std::shared_ptr<Shader> pointer_type;

        ShaderType get_type() const
        {
            return type;
        }

        template<typename ... Args>
        static pointer_type create(Args&& ... args)
        {
            return pointer_type{ new Shader(std::forward<Args>(args)...) };
        }

        ~Shader()
        {
            glDeleteShader(id);
        }

    protected:
        GLuint      id;
        ShaderType  type;
        std::string code;
    };
}