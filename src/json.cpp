#include "fakeprinter/json.hpp"
#include <fstream>
#include <map>
#include <iostream>

namespace printer {
namespace json_generator {

void generateSummaryJson(const std::vector<LayerData>& layers,
                        const std::filesystem::path& outputPath,
                        const std::string& printName,
                        bool supervisedMode) {
    std::filesystem::path summaryPath = outputPath / printName / "summary.json";
    std::ofstream jsonFile(summaryPath);
    
    // Calculate statistics
    int totalLayers = layers.size();
    int errorCount = 0;
    float avgLayerHeight = 0;
    float avgPrintSpeed = 0;
    float avgExtrusionTemp = 0;
    float avgInfillDensity = 0;
    float avgShellThickness = 0;
    float avgOverhangAngle = 0;
    float avgCoolingFanSpeed = 0;
    float avgZOffset = 0;
    float avgBedTemp = 0;
    
    std::map<std::string, int> errorTypes;
    std::map<std::string, int> materialCounts;
    std::map<std::string, int> infillPatternCounts;
    std::map<std::string, int> layerAdhesionCounts;
    
    for (const auto& layer : layers) {
        // Count error types
        errorTypes[layer.layer_error]++;
        if (layer.layer_error != "SUCCESS") errorCount++;
        
        // Calculate averages
        avgLayerHeight += layer.layer_height;
        avgPrintSpeed += layer.print_speed;
        avgExtrusionTemp += layer.extrusion_temp;
        avgInfillDensity += layer.infill_density;
        avgShellThickness += layer.shell_thickness;
        avgOverhangAngle += layer.overhang_angle;
        avgCoolingFanSpeed += layer.cooling_fan_speed;
        avgZOffset += layer.z_offset;
        avgBedTemp += layer.bed_temp;
        
        // Count various categories
        materialCounts[layer.material_type]++;
        infillPatternCounts[layer.infill_pattern]++;
        layerAdhesionCounts[layer.layer_adhesion]++;
    }
    
    // Calculate final averages
    if (totalLayers > 0) {
        avgLayerHeight /= totalLayers;
        avgPrintSpeed /= totalLayers;
        avgExtrusionTemp /= totalLayers;
        avgInfillDensity /= totalLayers;
        avgShellThickness /= totalLayers;
        avgOverhangAngle /= totalLayers;
        avgCoolingFanSpeed /= totalLayers;
        avgZOffset /= totalLayers;
        avgBedTemp /= totalLayers;
    }
    
    // Write JSON
    jsonFile << "{\n";
    jsonFile << "  \"printName\": \"" << printName << "\",\n";
    jsonFile << "  \"mode\": \"" << (supervisedMode ? "supervised" : "automatic") << "\",\n";
    jsonFile << "  \"statistics\": {\n";
    jsonFile << "    \"totalLayers\": " << totalLayers << ",\n";
    jsonFile << "    \"successfulLayers\": " << errorTypes["SUCCESS"] << ",\n";
    jsonFile << "    \"failedLayers\": " << errorCount << ",\n";
    jsonFile << "    \"averages\": {\n";
    jsonFile << "      \"layerHeight\": " << avgLayerHeight << ",\n";
    jsonFile << "      \"printSpeed\": " << avgPrintSpeed << ",\n";
    jsonFile << "      \"extrusionTemp\": " << avgExtrusionTemp << ",\n";
    jsonFile << "      \"infillDensity\": " << avgInfillDensity << ",\n";
    jsonFile << "      \"shellThickness\": " << avgShellThickness << ",\n";
    jsonFile << "      \"overhangAngle\": " << avgOverhangAngle << ",\n";
    jsonFile << "      \"coolingFanSpeed\": " << avgCoolingFanSpeed << ",\n";
    jsonFile << "      \"zOffset\": " << avgZOffset << ",\n";
    jsonFile << "      \"bedTemp\": " << avgBedTemp << "\n";
    jsonFile << "    },\n";
    
    // Write error types
    jsonFile << "    \"errorTypes\": [\n";
    for (auto it = errorTypes.begin(); it != errorTypes.end(); ++it) {
        jsonFile << "      {\"type\": \"" << it->first << "\", \"count\": " << it->second << "}";
        if (std::next(it) != errorTypes.end()) jsonFile << ",";
        jsonFile << "\n";
    }
    jsonFile << "    ],\n";
    
    // Write materials data
    jsonFile << "    \"materials\": [\n";
    for (auto it = materialCounts.begin(); it != materialCounts.end(); ++it) {
        jsonFile << "      {\"type\": \"" << it->first << "\", \"count\": " << it->second << "}";
        if (std::next(it) != materialCounts.end()) jsonFile << ",";
        jsonFile << "\n";
    }
    jsonFile << "    ],\n";
    
    // Write infill patterns data
    jsonFile << "    \"infillPatterns\": [\n";
    for (auto it = infillPatternCounts.begin(); it != infillPatternCounts.end(); ++it) {
        jsonFile << "      {\"pattern\": \"" << it->first << "\", \"count\": " << it->second << "}";
        if (std::next(it) != infillPatternCounts.end()) jsonFile << ",";
        jsonFile << "\n";
    }
    jsonFile << "    ],\n";
    
    // Write layer adhesion data
    jsonFile << "    \"layerAdhesion\": [\n";
    for (auto it = layerAdhesionCounts.begin(); it != layerAdhesionCounts.end(); ++it) {
        jsonFile << "      {\"type\": \"" << it->first << "\", \"count\": " << it->second << "}";
        if (std::next(it) != layerAdhesionCounts.end()) jsonFile << ",";
        jsonFile << "\n";
    }
    jsonFile << "    ]\n";
    jsonFile << "  }\n";
    jsonFile << "}\n";
}

} // namespace json_generator
} // namespace printer