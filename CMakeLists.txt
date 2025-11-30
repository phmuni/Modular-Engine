cmake_minimum_required(VERSION 3.10)

# Project name
project(modular-engine)
set(CMAKE_CXX_STANDARD 17)

# --- Debug ---
set(CMAKE_BUILD_TYPE Debug)

# --- Directories ---
# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
# Directory where external libraries are located
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")

# Include directories for project and external dependencies
include_directories(
    ${CMAKE_SOURCE_DIR}/internal
    ${EXTERNAL_DIR}
)
# --- Source files ---
# Recursively find all .cpp files in src and external folders
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/**/*.cpp" "${CMAKE_SOURCE_DIR}/external/**/*.cpp")
add_executable(engine ${SOURCE_FILES})

# --- Libraries ---
# Link external libraries manually
target_link_libraries(engine
    ${EXTERNAL_DIR}/SDL3/lib/libSDL3.dll.a
    # link other necessary libraries
)

# --- Copy DLLs ---
# Copy all DLLs from external dependencies to the bin folder after build
file(GLOB DLL_FILES "${EXTERNAL_DIR}/*/bin/*.dll")
foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DLL}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/"
    )
endforeach()
