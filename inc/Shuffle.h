#ifndef Shuffle_H
#define Shuffle_H
#include <algorithm>
#include "Task.h"
/// @brief Class put numMaps sorted containers to one sorted vector
class Shuffle {
public:
    VectorStr Work(std::vector<std::shared_ptr<VectorStr>> containers) {
        VectorStr merged;
    
        for (auto &cont : containers) {
            VectorStr tmp;
            
            std::merge(cont->begin(),cont->end(),
                        merged.begin(),merged.end(),
                        std::back_inserter(tmp));
            merged = tmp;    
        }
        return merged;
    }
};
#endif