#include "fakeprinter/summary.hpp"
#include "fakeprinter/json.hpp"
#include "fakeprinter/html.hpp"
#include <iostream>
#include <cstdlib>

namespace printer { 

PrintSummary::PrintSummary(const std::string& printName, 
                          const std::filesystem::path& outputPath,
                          bool supervisedMode)
    : printName_(printName)
    , outputPath_(outputPath)
    , supervisedMode_(supervisedMode) {
}

void PrintSummary::calculateStatistics(const std::vector<LayerData>& layers) {
    stats_ = PrintStatistics{};
    stats_.totalLayers = static_cast<int>(layers.size());
    stats_.successCount = 0;
    
    double totalLayerHeight = 0;
    double totalPrintSpeed = 0;
    double totalExtrusionTemp = 0;
    double totalInfillDensity = 0;
    double totalShellThickness = 0;
    double totalOverhangAngle = 0;
    double totalCoolingFanSpeed = 0;
    double totalZOffset = 0;
    double totalBedTemp = 0;
    
    for (const auto& layer : layers) {
        // Count success/errors
        if (layer.layer_error == "SUCCESS") {
            stats_.successCount++;
        } else {
            stats_.errorCount++;
        }
        stats_.errorTypes[layer.layer_error]++;
        
        // Count categories
        stats_.materialCounts[layer.material_type]++;
        stats_.infillPatternCounts[layer.infill_pattern]++;
        stats_.layerAdhesionCounts[layer.layer_adhesion]++;
        
        // Accumulate values for averages
        totalLayerHeight += layer.layer_height;
        totalPrintSpeed += layer.print_speed;
        totalExtrusionTemp += layer.extrusion_temp;
        totalInfillDensity += layer.infill_density;
        totalShellThickness += layer.shell_thickness;
        totalOverhangAngle += layer.overhang_angle;
        totalCoolingFanSpeed += layer.cooling_fan_speed;
        totalZOffset += layer.z_offset;
        totalBedTemp += layer.bed_temp;
    }
    
    // Calculate averages
    if (stats_.totalLayers > 0) {
        stats_.avgLayerHeight = totalLayerHeight / stats_.totalLayers;
        stats_.avgPrintSpeed = totalPrintSpeed / stats_.totalLayers;
        stats_.avgExtrusionTemp = totalExtrusionTemp / stats_.totalLayers;
        stats_.avgInfillDensity = totalInfillDensity / stats_.totalLayers;
        stats_.avgShellThickness = totalShellThickness / stats_.totalLayers;
        stats_.avgOverhangAngle = totalOverhangAngle / stats_.totalLayers;
        stats_.avgCoolingFanSpeed = totalCoolingFanSpeed / stats_.totalLayers;
        stats_.avgZOffset = totalZOffset / stats_.totalLayers;
        stats_.avgBedTemp = totalBedTemp / stats_.totalLayers;
    }
}

void PrintSummary::generateSummary(const std::vector<LayerData>& layers) {
    calculateStatistics(layers);
    
    // Generate JSON and HTML summaries
    json_generator::generateSummaryJson(layers, outputPath_, printName_, supervisedMode_);
    html_generator::generateHtmlViewer(outputPath_, printName_);
    
    // Display console output and open browser
    displayConsoleOutput();
    openInBrowser();
}

void PrintSummary::displayConsoleOutput() const {
    std::cout << "\n=== Print Summary ===\n";
    std::cout << "Print Name: " << printName_ << "\n";
    std::cout << "Mode: " << (supervisedMode_ ? "Supervised" : "Automatic") << "\n";
    
    std::cout << "\nLayer Statistics:\n";
    std::cout << "Total Layers Processed: " << stats_.totalLayers << "\n";
    std::cout << "Successful Layers: " << stats_.successCount << "\n";
    std::cout << "Failed Layers: " << stats_.errorCount << "\n";
    
    std::cout << "\nError Types Breakdown:\n";
    for (const auto& [error, count] : stats_.errorTypes) {
        std::cout << error << ": " << count << " layers\n";
    }
    
    std::cout << "\nOutput Information:\n";
    std::cout << "Directory: " << std::filesystem::absolute(outputPath_).string() << "\n";
    std::cout << "Summary Files Generated:\n";
    std::cout << "- summary.json (detailed statistics)\n";
    std::cout << "- summary.html (visual dashboard)\n";
}

void PrintSummary::openInBrowser() const {
    std::string command;
    #ifdef _WIN32
        command = "start ";
    #else
        command = "open ";
    #endif
    command += (outputPath_ / printName_ / "summary.html").string();
    std::system(command.c_str());
}

PrintStatistics PrintSummary::getStatistics() const {
    return stats_;
}

}