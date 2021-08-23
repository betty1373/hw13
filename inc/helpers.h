#pragma once
#include "classifier.h"
#include <istream>
#include <vector>
/// @file
/// @brief Helpers functions
/// @author btv<example@example.com>
using coef_t = std::vector<float>;
bool read_coef(std::istream& stream, coef_t& v);
bool read_features(std::istream& stream, kdd99::BinaryClassifier::features_t& features,size_t& classif);
