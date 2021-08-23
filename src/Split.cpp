#include "../inc/Split.h"

Split::Split(std::string fileName,std::size_t Threads) :
    m_file(fileName),
    m_Threads(Threads) {}

std::vector<FilePos> Split::Work() {
    if (!m_file.good()) {
        throw std::ifstream::failure("ReadFile error");
    }
    
    m_file.seekg(0,std::ios::end);
    long file_end = m_file.tellg();
    long section_Size = file_end / m_Threads;

    m_file.seekg(section_Size,std::ios::beg);
    return GetSections(section_Size,file_end); 
}

std::vector<FilePos> Split::GetSections(long sectionSize, long file_end) {
    std::vector<FilePos> sections;
    sections.reserve(m_Threads);

    long currPos = sectionSize;

    while ((currPos < file_end) && (currPos >=0))
    {
        auto buffer = '\0';
        m_file.seekg(currPos,std::ios::beg);
        
        while (buffer!='\n' && !m_file.fail()) {
            m_file.read(&buffer,1);
        } 

        currPos = m_file.tellg();
        if (currPos >= 0) {
            sections.push_back(currPos);
            currPos += sectionSize;
        }  
    }    
    sections.push_back(file_end);
    return sections;
}
