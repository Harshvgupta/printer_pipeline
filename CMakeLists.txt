cmake_minimum_required(VERSION 3.14)
project(Formlabs VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(${PROJECT_SOURCE_DIR}/include)


set(SOURCES
    src/fake_printer.cpp
    src/file_utils.cpp
    src/json.cpp
    src/html.cpp
    src/summary.cpp
    src/main.cpp
)


set(HEADERS
    include/fakeprinter/layer_data.hpp
    include/fakeprinter/fake_printer.hpp
    include/fakeprinter/file_utils.hpp
    include/fakeprinter/json.hpp
    include/fakeprinter/html.hpp
    include/fakeprinter/summary.hpp
)


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
