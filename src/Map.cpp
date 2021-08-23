#include "../inc/Map.h"
Map::Map(std::string fileName) :
    m_file(fileName) {}

std::vector<std::shared_ptr<VectorStr>> Map::Work(std::vector<FilePos> sections,
            std::function<void( std::ifstream &file, 
                                FilePos beg_pos,
                                FilePos end_pos,
                                std::shared_ptr<VectorStr> container)> map_func) {
    
    if (!m_file.good()) {
        throw std::ifstream::failure("ReadFile error");
    }
    std::vector<Task<std::shared_ptr<VectorStr>>> maps;
    
    FilePos beg_pos(0),end_pos(0);
    for (auto &section : sections) {
        end_pos = section;

        Task<std::shared_ptr<VectorStr>> task;

        task.taskResult = std::make_shared<VectorStr>();
        task.task = std::make_shared<std::thread>(map_func, std::ref(m_file), beg_pos,
                                                  end_pos, task.taskResult);
        maps.push_back(task);
        beg_pos = end_pos;
    }
    {
        std::vector<std::shared_ptr<VectorStr>> containers;
        for (auto &task : maps)
        {   
            task.task->join();
            std::shared_ptr<VectorStr> container(task.taskResult);
            std::sort(container->begin(),container->end());
            containers.push_back(container);
        }
        return containers;
    }
}
