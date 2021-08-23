#include "../inc/logreg_classifier.h"
#include "../inc/helpers.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <iterator>
#include <cassert>
using kdd99::LogregClassifier;
/// @file
/// @brief Main function. CV test
/// @author btv<example@example.com>

int main(int argc, char** argv) {
    
    if (argc < 3) {
      std::cout << "Need params <file_name_test_data> <file_name_model>"<<std::endl;
      return -1;
    }
    int n_classes = 10;

    std::string file_test = argv[1];
    std::string file_model = argv[2];
    
    //std::vector<coef_t> v_coef;
   // v_coef.reserve(n_classes);

    std::vector<std::pair<LogregClassifier,float>> v_pred;
    v_pred.reserve(n_classes);

    std::ifstream istream{file_model};
    assert(istream.is_open());
    size_t i=0;
    for (;;) {
        coef_t coef;
        if (!read_coef(istream, coef)) {
            break;
        }
        i++;
        //v_coef.push_back(coef);
        v_pred.push_back(std::make_pair(LogregClassifier{coef},0.0));
    }
    n_classes = i;
    auto features = LogregClassifier::features_t{};
    double pred_y = 0;
    size_t m_class,pred_class; 
    double n_test=0,n_false = 0;

    std::ifstream test_data{file_test};
    assert(test_data.is_open());
   
    for (;;) {
        if (!read_features(test_data, features,m_class)) {
            break;
        }
        n_test++;
        pred_y = 0;
        pred_class = 0;
       
        for (int i = 0; i<n_classes;i++) {
            v_pred[i].second = v_pred[i].first.predict_proba(features);
            
            if (v_pred[i].second >=pred_y) {
                pred_y = v_pred[i].second;
                pred_class = i;
            }
        }
        if (pred_class != m_class) {
            n_false++;
        //      std::cout<<n_test<<" "<<m_class<<" ";
        //     for (int i =0; i<n_classes;i++) {
        //             std::cout<<i<<" "<<v_pred[i].second<<" ";
        //     }
        //     std::cout<<pred_class<<" "<<pred_y<<" "<<n_false<<std::endl;  
        }
    }
    double accuracy = 1 - n_false/n_test;
    std::cout<<"Total obj:"<<n_test<<" False obj:"<<n_false<<" Accuracy:"<<accuracy<<std::endl;
    return 0;
}  
