// utilities.cpp
#include "utilities.h"
#include <fstream>
#include <iostream>
#include <numeric>  // For std::accumulate

void save_multiple_vectors_to_file(const std::vector<std::vector<int>>& vectors, const std::string& filename) {
    std::ofstream outfile(filename);

    if (!outfile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < vectors.size(); ++i) {
        outfile << "Vector " << (i + 1) << ":\n";
        for (const auto& element : vectors[i]) {
            outfile << element << " ";
        }
        outfile << "\n";
    }

    outfile.close();
    if (outfile.good()) {
        std::cout << "Vectors successfully saved to " << filename << std::endl;
    } else {
        std::cerr << "Error occurred while saving to file." << std::endl;
    }
}

double calculate_average(const std::vector<int>& vec) {
    if (vec.empty()) {
        return 0.0;
    }

    double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    return sum / vec.size();
}
