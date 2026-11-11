cmake_minimum_required(VERSION 3.16)
project(Pacman)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(PTSD)
#add_library(Framework ${PTSD_SRC_FILES} $<TARGET_OBJECTS:PracticalToolsForSimpleDesign>)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}
    ${SRC_FILES}
    ${HEADER_FILES}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# PORTABLE=ON: build a distributable exe that loads Resources/ and assets/
# from the folder next to it (relative paths) instead of the source tree.
option(PORTABLE "Use relative resource paths and copy resources next to the executable" OFF)

if(PORTABLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="Resources")

    # Override PTSD's absolute PTSD_ASSETS_DIR without editing the PTSD submodule.
    get_target_property(PTSD_DEFS PTSD COMPILE_DEFINITIONS)
    list(FILTER PTSD_DEFS EXCLUDE REGEX "^PTSD_ASSETS_DIR=")
    list(APPEND PTSD_DEFS PTSD_ASSETS_DIR="assets")
    set_target_properties(PTSD PROPERTIES COMPILE_DEFINITIONS "${PTSD_DEFS}")

    # Copy game resources and the shaders PTSD needs next to the executable.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/assets/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/shaders
    )

    # No console window when launched by double-click.
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)

    # MinGW: link libstdc++/libgcc/winpthread statically so no runtime DLLs are needed.
    if(MINGW)
        target_link_options(${PROJECT_NAME} PRIVATE -static)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    message(FATAL_ERROR "Non-Debug builds need -DPORTABLE=ON (relative resource paths).")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_link_libraries(Framework
#    ${DEPENDENCY_LINK_LIBRARIES}
#)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
#    Framework
        PTSD
)
