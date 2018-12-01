
#include <types.hpp>
#include <query.hpp>
#include <relation.hpp>

#include <unordered_map>
#include <vector>
#include <string>

#include <list.hpp>
#include <pair.hpp>



namespace RHJ
{

    class Executioner {

        struct Entity {

            std::size_t columnSize;     // Number of Values in each Column
            std::size_t columnNum;      // Number of Columns

            std::unordered_map<std::size_t, std::vector<tuple_key_t> > map;

            Entity(std::size_t _columnNum, std::size_t _columnSize, std::unordered_map<std::size_t, std::vector<tuple_key_t>> _map);
            ~Entity();

        };

        struct IntermediateResults : public utility::list<Entity> {

            IntermediateResults();
            ~IntermediateResults();

            utility::pair<iterator, iterator> find(std::size_t Rel_1, std::size_t Rel_2);
            iterator find(std::size_t Rel);

        } inteResults;

        void executeFilter(const Query& query, Query::Predicate pred);

        void executeJoin(const Query& query, Query::Predicate pred);

        void externalJoin(const Query& query, Query::Predicate::Operand inner, Query::Predicate::Operand outer);

        void semiInternalJoin(const Query& query, Query::Predicate::Operand inner, IntermediateResults::iterator innerIt, Query::Predicate::Operand outer);

        void internalJoin(const Query& query, Query::Predicate::Operand inner, IntermediateResults::iterator innerIt, 
                                              Query::Predicate::Operand outer, IntermediateResults::iterator outerIt);

        void internalSelfJoin(const Query& query, Query::Predicate::Operand inner, IntermediateResults::iterator innerIt, Query::Predicate::Operand outer);
        void externalSelfJoin(const Query& query, Query::Predicate::Operand inner, Query::Predicate::Operand outer);

        void cartesianProduct(IntermediateResults::iterator left, IntermediateResults::iterator right);

        using Checksum = Query::Predicate::Operand;
        std::vector<std::string> calculateCheckSums(const Query& query);

        bool compare(tuple_payload_t u, tuple_key_t v, Query::Predicate::Type op);

    public:

        Executioner();
        ~Executioner();

        std::vector<std::string> execute(const Query& query);
    };
}

std::vector<std::size_t> findIndexes(std::vector<tuple_key_t> vec, tuple_key_t val);



