#include "kernel_token_view.h"

namespace qk::kernel
{

    TokenView::TokenView(Token* start, Token* end):
        pStart(start), pEnd(end)
    {

    }
    Token* TokenView::command() const
    {
        return pStart;
    }
    Token* TokenView::terminator() const
    {
        return pEnd;
    }


    Token& TokenView::Iterator::operator*() const { return *ptr; }

    TokenView::Iterator& TokenView::Iterator::operator++() {
        ++ptr;
        return *this;
    }

    bool TokenView::Iterator::operator!=(const TokenView::Iterator& other) const {
        return ptr != other.ptr;
    }

    TokenView::Iterator TokenView::begin() const {
        return TokenView::Iterator{ pStart + 1 };
    }

    TokenView::Iterator TokenView::end() const {
        return TokenView::Iterator{ pEnd }; // +1 for inclusive end
    }

    size_t TokenView::size() const
    {
        return static_cast<size_t>(pEnd - pStart);
    }

    Token& TokenView::operator[](size_t index) const
    {
        assert(index < size());
        return *(pStart + index);
    }




}
