// utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>

void save_multiple_vectors_to_file(const std::vector<std::vector<int>>& vectors, const std::string& filename);
double calculate_average(const std::vector<int>& vec);

#endif // UTILITIES_H
