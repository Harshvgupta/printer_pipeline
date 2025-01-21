#pragma once

#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include "layer_data.hpp"

namespace printer {

struct PrintStatistics {
    PrintStatistics() : 
        totalLayers(0), 
        successCount(0), 
        errorCount(0),
        avgLayerHeight(0.0),
        avgPrintSpeed(0.0),
        avgExtrusionTemp(0.0),
        avgInfillDensity(0.0),
        avgShellThickness(0.0),
        avgOverhangAngle(0.0),
        avgCoolingFanSpeed(0.0),
        avgZOffset(0.0),
        avgBedTemp(0.0) {}

    int totalLayers;
    int successCount;
    int errorCount;
    std::map<std::string, int> errorTypes;
    std::map<std::string, int> materialCounts;
    std::map<std::string, int> infillPatternCounts;
    std::map<std::string, int> layerAdhesionCounts;

    double avgLayerHeight;
    double avgPrintSpeed;
    double avgExtrusionTemp;
    double avgInfillDensity;
    double avgShellThickness;
    double avgOverhangAngle;
    double avgCoolingFanSpeed;
    double avgZOffset;
    double avgBedTemp;
};

class PrintSummary {
public:
    PrintSummary(const std::string& printName, 
                 const std::filesystem::path& outputPath,
                 bool supervisedMode);

    void generateSummary(const std::vector<LayerData>& layers);
    void displayConsoleOutput() const;
    PrintStatistics getStatistics() const;

private:
    void calculateStatistics(const std::vector<LayerData>& layers);
    void openInBrowser() const;

    std::string printName_;
    std::filesystem::path outputPath_;
    bool supervisedMode_;
    PrintStatistics stats_;
};

}