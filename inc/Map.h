#ifndef Map_H
#define Map_H
#include "Task.h"
/// @brief Class put file sections to numMaps sorted containers
class Map {
public:
    Map(std::string fileName);
    std::vector<std::shared_ptr<VectorStr>> Work(std::vector<FilePos> sections,
            std::function<void(std::ifstream &file, FilePos beg_pos,FilePos end_pos,
                               std::shared_ptr<VectorStr> vectorStr)> map_func);
    std::mutex m_Mutex;
private:
    Map() =  delete;
    std::ifstream m_file;
};
#endif