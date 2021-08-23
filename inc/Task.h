#ifndef Task_H
#define Task_H
#include <fstream>
#include <functional>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

using VectorStr = std::vector<std::string>;
using FilePos = std::ifstream::pos_type;
template <typename T> struct Task {
    std::shared_ptr<std::thread> task;
    T taskResult;
};
#endif