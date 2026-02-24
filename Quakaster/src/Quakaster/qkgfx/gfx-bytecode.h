#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include "../Core.h"
#include <string>
#include <format>


namespace qk::gfx::bytecode
{

    // --- Operand Types ---
    enum class EOperandType : uint32_t
    {
        NONE,
        GLSIZEI,
        GLENUM,
        GLUINT,
        FLOAT,
        FLAGS,
        INT,
        PTR
    };

    


    // --- Operand Payload ---
    union UOperandValue
    {
        float       f;
        int         i;
        GLuint      handle;
        GLenum      option;
        GLbitfield  flags;
        GLsizei     size;
        const void* ptr;

        UOperandValue() : ptr(nullptr) {}
    };



    // --- Opcodes ---
    enum class EOpcode : uint32_t
    {
        NONE,
        BREAKPOINT,
        SET_R0,
        SET_R1,
        SET_R2,
        SET_R3,
        BIND_VERTEX_OBJECT,
        BIND_VERTEX_BUFFER,
        BIND_ELEMENT_BUFFER,
        SET_CLEAR_COLOR,
        CLEAR,
        DRAW_VERTEX_OBJECT
    };

    template <class T>
    bool is_type(EOperandType type)
    {
        using enum EOperandType;

        if constexpr (std::is_same_v<T, GLsizei>())
            return type == GLSIZEI;
        if constexpr (std::is_same_v<T, GLuint>())
            return type == GLUINT;
        if constexpr (std::is_same_v<T, GLenum>())
            return type == GLENUM;
        if constexpr (std::is_same_v<T, GLbitfield>())
            return type == FLAGS;
        if constexpr (std::is_same_v<T, void>())
            return type == NONE;
        if constexpr (std::is_same_v<T, int>())
            return type == INT;
        if constexpr (std::is_same_v<T, float>())
            return type == FLOAT;
        if constexpr (std::is_pointer_v<T>())
            return type == PTR;
        return false;
    }

    /// <summary>
    /// represents, simultaneusly (and depending on context) bytecode for 
    /// </summary>
    struct Instruction
    {
        UOperandValue value;
        EOperandType  type;
        public:
            EOpcode  opcode;
            template <class T>
            bool is()
            {
                return qk::gfx::bytecode::is_type<T>(type);
            }

            template <class T>
            T* as()
            {
                if (!is<T>()) return nullptr;

               //...

            }



    };

    static_assert(sizeof(Instruction) == 16);



}