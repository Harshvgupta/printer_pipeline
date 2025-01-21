#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "layer_data.hpp"
#include "summary.hpp"

namespace printer {

class FakePrinter {
public:
    FakePrinter(const std::string& printName, 
                const std::string& outputDir, 
                bool supervisedMode);

    void run();

private:
    bool setupOutputDir();
    bool processLayer(const LayerData& layer);
    void runSupervised(const std::vector<LayerData>& layers);
    void runAutomatic(const std::vector<LayerData>& layers);

    std::string printName_;
    std::string outputDir_;
    bool supervisedMode_;
    std::filesystem::path basePath_;
    std::string csvFile_;
    std::string outputPath_;
    PrintSummary summary_;  
};

}

