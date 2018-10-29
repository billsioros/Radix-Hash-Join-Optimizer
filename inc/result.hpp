
#pragma once

#include <types.hpp>

#define CAPACITY (1024UL * 1024UL / sizeof(Result))

namespace RHJ
{
    struct List
    {
        struct Result {
            tuple_key_t key1;
            tuple_key_t key2;
        };

        struct Node
        {
            class Buffer
            {
                friend List;

                std::size_t _size;
                Result _data[CAPACITY];

            public:

                std::size_t size() const { return _size; }
                const Result& operator[](std::size_t i) const { return _data[i]; }
            } buffer;

            Node * next;

            Node();
            ~Node();
        } * head, * tail;

        List();
        List(List&&) noexcept;

        ~List();

        List& operator=(List&&) noexcept;

        void append(const Result&);
    };
}
