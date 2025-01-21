#include "fakeprinter/fake_printer.hpp"
#include "fakeprinter/file_utils.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem; 


namespace printer {

FakePrinter::FakePrinter(const std::string& printName, 
                         const std::string& outputDir, 
                         bool supervisedMode)
    : printName_(printName)
    , outputDir_(outputDir)
    , supervisedMode_(supervisedMode)
    , basePath_(fs::current_path().parent_path())
    , csvFile_((fs::current_path().parent_path() / "data" / "fl_coding_challenge_v1.csv").string())
    , outputPath_((fs::current_path().parent_path() / "output").string())
    , summary_(printName, 
              fs::path(outputPath_),  // Use the namespace alias
              supervisedMode) {
}

void FakePrinter::run() {
    std::cout << "CSV File Path: " << csvFile_ << "\n";
    std::cout << "Output Directory: " << outputPath_ << "\n";

    if (!setupOutputDir()) {
        std::cerr << "Failed to create output directory\n";
        return;
    }

    auto layers = file_utils::readCsvData(csvFile_, supervisedMode_);
    if (layers.empty()) {
        std::cerr << "No data was read from the CSV file\n";
        return;
    }

    std::cout << "Found " << layers.size() << " layers to process\n";
    
    if (supervisedMode_) {
        runSupervised(layers);
    } else {
        runAutomatic(layers);
    }

    summary_.generateSummary(layers);
}

bool FakePrinter::setupOutputDir() {
    try {
        std::filesystem::create_directories(outputPath_);
        std::filesystem::path printDir = std::filesystem::path(outputPath_) / printName_;
        std::filesystem::create_directories(printDir);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << "\n";
        return false;
    }
}

bool FakePrinter::processLayer(const LayerData& layer) {
    try {
        std::filesystem::path printDir = std::filesystem::path(outputPath_) / printName_;
        std::filesystem::path layerDir = printDir / ("layer_" + std::to_string(layer.layer_number));
        std::filesystem::create_directories(layerDir);

        std::filesystem::path infoFile = layerDir / "info.txt";
        std::ofstream output(infoFile);
        if (!output.is_open()) {
            std::cerr << "Could not create info file: " << infoFile.string() << "\n";
            return false;
        }
        
        // Write layer data
        output << "Layer Number: " << layer.layer_number << "\n";
        output << "Layer Error: " << layer.layer_error << "\n";
        output << "Layer Height: " << layer.layer_height << "\n";
        output << "Material Type: " << layer.material_type << "\n";
        output << "Extrusion Temperature: " << layer.extrusion_temp << "\n";
        output << "Print Speed: " << layer.print_speed << "\n";
        output << "Layer Adhesion: " << layer.layer_adhesion << "\n";
        output << "Infill Density: " << layer.infill_density << "\n";
        output << "Infill Pattern: " << layer.infill_pattern << "\n";
        output << "Shell Thickness: " << layer.shell_thickness << "\n";
        output << "Overhang Angle: " << layer.overhang_angle << "\n";
        output << "Cooling Fan Speed: " << layer.cooling_fan_speed << "\n";
        output << "Retraction Settings: " << layer.retraction_settings << "\n";
        output << "Z-Offset: " << layer.z_offset << "\n";
        output << "Bed Temperature: " << layer.bed_temp << "\n";
        output << "Layer Time: " << layer.layer_time << "\n";
        output << "File Name: " << layer.file_name << "\n";
        output << "Image URL: " << layer.image_url << "\n";
        
        std::cout << "Processed layer " << layer.layer_number 
                 << " -> " << infoFile.string() << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error processing layer: " << e.what() << "\n";
        return false;
    }
}

void FakePrinter::runSupervised(const std::vector<LayerData>& layers) {
    std::string input;
    for (const auto& layer : layers) {
        if (layer.layer_error != "SUCCESS") {
            std::cout << "\nLayer " << layer.layer_number << " has an error: " 
                      << layer.layer_error << "\n";
            std::cout << "Press Enter to ignore the error and continue processing, "
                         "or type 'end' to stop the fake print: ";
            std::getline(std::cin, input);
            if (input == "end") {
                std::cout << "Ending print by user request due to layer error\n";
                break;
            }
        }

        std::cout << "\nPress Enter to process layer " 
                  << layer.layer_number 
                  << " (or type 'end' to stop): ";
        std::getline(std::cin, input);
        
        if (input == "end") {
            std::cout << "Ending print by user request\n";
            break;
        }

        if (!processLayer(layer)) {
            std::cout << "Error processing layer " << layer.layer_number 
                      << ". Type 'ignore' to continue or 'end' to stop: ";
            std::getline(std::cin, input);
            if (input == "end") break;
        }
    }
}

void FakePrinter::runAutomatic(const std::vector<LayerData>& layers) {
    std::cout << "Processing layers automatically...\n";
    for (const auto& layer : layers) {
        processLayer(layer);
    }
}

} 