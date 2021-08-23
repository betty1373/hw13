#include "../inc/Reduce.h"
#include <algorithm>

Reduce::Reduce(VectorStr data, size_t numThreads)
    : m_data(data), 
      m_Threads(numThreads) {}

void Reduce::Work(fncToReduce reduce_func) {

  	std::vector<std::shared_ptr<VectorStr>> containers(m_Threads);
 	std::generate(containers.begin(), containers.end(),
                []() { return std::make_shared<VectorStr>();});
  	{
    	for (auto &part : m_data) {
      		std::hash<std::string> hash;
      		containers[(part.empty()) ? 0 : (hash(part) % m_Threads)]->push_back(part);
    	}
  	}
  	{
    	std::vector<Task<std::shared_ptr<std::ofstream>>> reducers;

    	for (size_t i = 0; i < m_Threads; i++) {
    
        	Task<std::shared_ptr<std::ofstream>> task;
      		task.taskResult = std::make_shared<std::ofstream>("reducer_" + std::to_string(i) + ".txt");
      		task.task = std::make_shared<std::thread>(reduce_func, std::ref(containers[i]), task.taskResult);
      		reducers.push_back(task);
    	}
    	{
      		for (auto &reducer : reducers)
        		reducer.task->join();
      		reducers.clear();
    	}
  	}
}
