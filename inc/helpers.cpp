#include "helpers.h"
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
bool read_coef(std::istream& stream, coef_t& v) {
    std::string line,str;
    std::getline(stream, line);

    v.clear();
    char delimiter=' ';  
    std::istringstream linestream{line};
    double value;
    while (std::getline(linestream,str,delimiter)) {
        value = atof(str.c_str());
        v.push_back(value);
    }
    return stream.good();
}

bool read_features(std::istream& stream, kdd99::BinaryClassifier::features_t& features,size_t& classif ) {
    std::string line,str;
    std::getline(stream, line);
   
    features.clear();
    std::istringstream linestream{line};

    double value;
    char delimiter=',';    
    int i = 0;

    while (std::getline(linestream,str,delimiter)) {
        if (i==0) {
            classif = atoi(str.c_str());
        }
        else {
            value = atof(str.c_str());
            features.push_back(value);
        }
        i++;
    }
    return stream.good();
}
