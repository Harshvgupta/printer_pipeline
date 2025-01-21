// html
#pragma once

#include <string>
#include <filesystem>

namespace printer {
namespace html_generator {

void generateHtmlViewer(const std::filesystem::path& outputPath,
                       const std::string& printName);

} 
} 