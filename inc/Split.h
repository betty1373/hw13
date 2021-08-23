#ifndef Split_H
#define Split_H
#include "Task.h"
/// @brief Class split file to numMaps sections
class Split {
public:
    Split(std::string fileName,std::size_t numThreads);
    std::vector<FilePos> Work();
private:
    Split()=delete;
    std::vector<FilePos> GetSections(long sectionSize,long end_pos);
    std::ifstream m_file;
    std::size_t m_Threads;
};
#endif