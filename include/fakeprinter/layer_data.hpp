#pragma once

#include <string>

namespace printer {

struct LayerData {
    std::string layer_error;
    int layer_number;
    float layer_height;
    std::string material_type;
    int extrusion_temp;
    int print_speed;
    std::string layer_adhesion;
    int infill_density;
    std::string infill_pattern;
    int shell_thickness;
    int overhang_angle;
    int cooling_fan_speed;
    std::string retraction_settings;
    float z_offset;
    int bed_temp;
    std::string layer_time;
    std::string file_name;
    std::string image_url;
};

}