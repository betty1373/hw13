#ifndef Reduce_H
#define Reduce_H
#include "Task.h"
/// @brief Class put to one sorted vector to reduceNums threads to find minimal prefix
class Reduce {
public:
    using fncToReduce = std::function<void(std::shared_ptr<VectorStr> &data,
                                    std::shared_ptr<std::ofstream> out)>;
    Reduce(VectorStr data,std::size_t numThreads);
    void Work(fncToReduce reduce_func);
private:
    Reduce() =  delete;
    VectorStr m_data;
    std::size_t m_Threads;
};
#endif