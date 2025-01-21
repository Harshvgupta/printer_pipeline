// json_generator.hpp
#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "fakeprinter/layer_data.hpp"

namespace printer {
namespace json_generator {

void generateSummaryJson(const std::vector<LayerData>& layers,
                        const std::filesystem::path& outputPath,
                        const std::string& printName,
                        bool supervisedMode);

} 
} 

