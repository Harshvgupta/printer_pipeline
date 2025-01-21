#include "fakeprinter/file_utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace printer {
namespace file_utils {

std::string parseCSVCell(std::stringstream& ss) {
    std::string cell;
    char c;
    bool inQuotes = false;
    cell.clear();

    while (ss.get(c)) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            return cell;
        } else {
            cell += c;
        }
    }
    return cell;
}

std::vector<LayerData> readCsvData(const std::string& csvFile, bool supervisedMode) {
    std::vector<LayerData> layers;
    std::ifstream file(csvFile);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << csvFile << "\n";
        return layers;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    // Read data rows
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        LayerData layer;

        try {
            layer.layer_error = parseCSVCell(ss);
            layer.layer_number = std::stoi(parseCSVCell(ss));
            layer.layer_height = std::stof(parseCSVCell(ss));
            layer.material_type = parseCSVCell(ss);
            layer.extrusion_temp = std::stoi(parseCSVCell(ss));
            layer.print_speed = std::stoi(parseCSVCell(ss));
            layer.layer_adhesion = parseCSVCell(ss);
            layer.infill_density = std::stoi(parseCSVCell(ss));
            layer.infill_pattern = parseCSVCell(ss);
            layer.shell_thickness = std::stoi(parseCSVCell(ss));
            layer.overhang_angle = std::stoi(parseCSVCell(ss));
            layer.cooling_fan_speed = std::stoi(parseCSVCell(ss));
            layer.retraction_settings = parseCSVCell(ss);
            layer.z_offset = std::stof(parseCSVCell(ss));
            layer.bed_temp = std::stoi(parseCSVCell(ss));
            layer.layer_time = parseCSVCell(ss);
            layer.file_name = parseCSVCell(ss);
            layer.image_url = parseCSVCell(ss);
            
            layers.push_back(layer);
            std::cout << "Read layer " << layer.layer_number << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << "\n";
            std::cerr << "Error: " << e.what() << "\n";
            if (supervisedMode) {
                std::cout << "Error in parsing. Continue? (y/n): ";
                std::string response;
                std::getline(std::cin, response);
                if (response != "y") break;
            }
        }
    }

    return layers;
}

}
} 