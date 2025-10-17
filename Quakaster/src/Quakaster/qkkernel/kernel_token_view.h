#pragma once
#include "kernel_token.h"
#include "../Core.h"


namespace qk::kernel
{
    class QK_API TokenView {
        Token* pStart;
        Token* pEnd; // inclusive terminator
    public:

        TokenView(Token* start, Token* end);

        Token* command() const;
        Token* terminator() const;

        struct QK_API Iterator {
            Token* ptr;
            Token& operator*() const;
            Iterator& operator++();
            bool operator!=(const Iterator& other) const;
        };
        Token& operator[](size_t index) const;
        Iterator begin() const;
        Iterator end() const;
        size_t size() const;
    };
}