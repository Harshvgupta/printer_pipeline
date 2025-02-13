#include "fakeprinter/html.hpp"
#include <fstream>
#include <sstream>

namespace printer {
namespace html_generator {

void generateHtmlViewer(const std::filesystem::path& outputPath,
                       const std::string& printName) {
    std::filesystem::path htmlPath = outputPath / printName / "summary.html";
    std::ofstream htmlFile(htmlPath);
    
    // Read the JSON file content directly
    std::filesystem::path jsonPath = outputPath / printName / "summary.json";
    std::ifstream jsonFile(jsonPath);
    std::string jsonContent((std::istreambuf_iterator<char>(jsonFile)),
                           std::istreambuf_iterator<char>());
    
    htmlFile << R"(
<!DOCTYPE html>
<html>
<head>
    <title>Print Summary</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/react/17.0.2/umd/react.production.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/react-dom/17.0.2/umd/react-dom.production.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/recharts/2.1.9/Recharts.js"></script>
    <link href="https://cdn.jsdelivr.net/npm/tailwindcss@2.2.19/dist/tailwind.min.css" rel="stylesheet">
</head>
<body class="bg-gray-100">
    <div id="root"></div>
    <script>
        // Embed JSON data directly in the HTML
        const data = )" << jsonContent << R"(;
        
        // Now use the data directly without fetch
        const root = document.getElementById('root');
        root.innerHTML = `
            <div class="max-w-7xl mx-auto py-6 px-4">
                <h1 class="text-3xl font-bold mb-6">Print Summary: ${data.printName}</h1>
                
                <!-- Basic Stats -->
                <div class="grid grid-cols-1 md:grid-cols-3 gap-4 mb-6">
                    <div class="bg-white p-6 rounded-lg shadow">
                        <h2 class="text-xl font-semibold">Total Layers</h2>
                        <p class="text-3xl font-bold">${data.statistics.totalLayers}</p>
                    </div>
                    <div class="bg-white p-6 rounded-lg shadow">
                        <h2 class="text-xl font-semibold">Successful Layers</h2>
                        <p class="text-3xl font-bold text-green-600">${data.statistics.successfulLayers}</p>
                    </div>
                    <div class="bg-white p-6 rounded-lg shadow">
                        <h2 class="text-xl font-semibold">Failed Layers</h2>
                        <p class="text-3xl font-bold text-red-600">${data.statistics.failedLayers}</p>
                    </div>
                </div>

                <!-- Averages -->
                <div class="bg-white p-6 rounded-lg shadow mb-6">
                    <h2 class="text-2xl font-bold mb-4">Print Averages</h2>
                    <div class="grid grid-cols-2 md:grid-cols-4 gap-4">
                        <div>
                            <h3 class="font-semibold">Layer Height</h3>
                            <p>${data.statistics.averages.layerHeight.toFixed(2)} mm</p>
                        </div>
                        <div>
                            <h3 class="font-semibold">Print Speed</h3>
                            <p>${data.statistics.averages.printSpeed.toFixed(2)} mm/s</p>
                        </div>
                        <div>
                            <h3 class="font-semibold">Extrusion Temp</h3>
                            <p>${data.statistics.averages.extrusionTemp.toFixed(1)}°C</p>
                        </div>
                        <div>
                            <h3 class="font-semibold">Bed Temp</h3>
                            <p>${data.statistics.averages.bedTemp.toFixed(1)}°C</p>
                        </div>
                    </div>
                </div>

                <!-- Error Types -->
                <div class="bg-white p-6 rounded-lg shadow mb-6">
                    <h2 class="text-2xl font-bold mb-4">Error Types</h2>
                    <div class="space-y-2">
                        ${data.statistics.errorTypes.map(error => `
                            <div class="flex justify-between items-center">
                                <span>${error.type}</span>
                                <span class="font-bold">${error.count}</span>
                            </div>
                        `).join('')}
                    </div>
                </div>

                <!-- Materials -->
                <div class="bg-white p-6 rounded-lg shadow mb-6">
                    <h2 class="text-2xl font-bold mb-4">Materials Used</h2>
                    <div class="space-y-2">
                        ${data.statistics.materials.map(material => `
                            <div class="flex justify-between items-center">
                                <span>${material.type}</span>
                                <span class="font-bold">${material.count} layers</span>
                            </div>
                        `).join('')}
                    </div>
                </div>

                <!-- Infill Patterns -->
                <div class="bg-white p-6 rounded-lg shadow mb-6">
                    <h2 class="text-2xl font-bold mb-4">Infill Patterns</h2>
                    <div class="space-y-2">
                        ${data.statistics.infillPatterns.map(pattern => `
                            <div class="flex justify-between items-center">
                                <span>${pattern.pattern}</span>
                                <span class="font-bold">${pattern.count} layers</span>
                            </div>
                        `).join('')}
                    </div>
                </div>
            </div>
        `;
    </script>
</body>
</html>)";
}
}}