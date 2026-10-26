#pragma once
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


inline std::vector<int> mat_vec(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vec) {
    std::vector<int> result(matrix.size()); // matrix.size() = number of rows

    for (std::size_t i = 0; i < matrix.size(); i++) {
        int dot_product = 0;
        for (std::size_t j = 0; j < matrix[i].size(); j++) {
            dot_product += matrix[i][j] * vec[j];
        }
        result[i] = dot_product;
    }

    return result;
}
