/*
    Testing RHJ::Index::join
*/

#include <index.hpp>
#include <iostream>

int main()
{
    RHJ::PsumTable::Bucket a = { new RHJ::Relation::Tuple[10UL], 10UL };
    RHJ::PsumTable::Bucket b = { new RHJ::Relation::Tuple[10UL], 10UL };
    for (std::size_t i = 0UL; i < a.size; i++)
    {
        a.tuples[i].payload = a.tuples[i].key = i;
        b.tuples[i].payload = b.tuples[i].key = i;
    }

    RHJ::List results;
    RHJ::Index index(a);

    index.join(b, results, RHJ::Index::Order::first);

    for (RHJ::List::Node * current = results.head; current; current = current->next)
    {
        for (std::size_t i = 0UL; i < current->buffer.size(); i++)
        {
            std::cout
            << "["
            << current->buffer[i].key1
            << ", "
            << current->buffer[i].key2
            << "]"
            << std::endl;
        }
    }

    delete[] a.tuples; delete[] b.tuples;
}
