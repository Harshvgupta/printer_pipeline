#pragma once

#include <string>
#include <vector>
#include "fakeprinter/layer_data.hpp"

namespace printer {
namespace file_utils {

std::string parseCSVCell(std::stringstream& ss);
std::vector<LayerData> readCsvData(const std::string& csvFile, bool supervisedMode);

} 
} 