# Set CMake version number
cmake_minimum_required(VERSION 3.16)

# Change "Temp-Projekt" to your project name
project(Walnut-CMake VERSION 0.2.0 LANGUAGES CXX)

#----------------------------------------------------------------------------------------------
# Part till line 25 is very very similar to that of @codetechandtutorials

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote --merge
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#----------------------------------------------------------------------------------------------

# adding all files needed to compile the project
add_library(${PROJECT_NAME}

    external/Walnut/Walnut/src/Walnut/Application.cpp
    external/Walnut/Walnut/src/Walnut/Image.cpp
    external/Walnut/Walnut/src/Walnut/Random.cpp
    external/Walnut/Walnut/src/Walnut/ImGui/ImGuiBuild.cpp

    external/Walnut/vendor/imgui/imgui_draw.cpp
    external/Walnut/vendor/imgui/imgui_demo.cpp
    external/Walnut/vendor/imgui/imgui_tables.cpp
    external/Walnut/vendor/imgui/imgui_widgets.cpp
    external/Walnut/vendor/imgui/imgui.cpp

)

add_subdirectory(
    external/Walnut/vendor/glm
)

# The glfw that is included in the Walnut project is not compatible with CMake for some reason
add_subdirectory(
    external/glfw
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# same standard that The Cherno uses
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


# Defining WL_PLATFORM_WINDOWS WL_DEBUG where applicable

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG; WL_PLATFORM_WINDOWS; WL_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:DEBUG; WL_PLATFORM_WINDOWS; WL_DEBUG>
        $<$<CONFIG:Release>:NDEBUG; WL_PLATFORM_WINDOWS>
        $<$<CONFIG:MinSizeRel>:NDEBUG; WL_PLATFORM_WINDOWS>
    )
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG; WL_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:DEBUG; WL_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:MinSizeRel>:NDEBUG>
    )
endif()

# <-- Added directories to include directory here: -->
target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/Walnut/vendor/glm
    PUBLIC external/Walnut/vendor/imgui
    PUBLIC external/Walnut/vendor/stb_image
    PUBLIC external/Walnut/Walnut/src
    PUBLIC $ENV{VULKAN_SDK}/include
)


# <-- Added directory of external libs to link here: -->
target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
)

find_package(Vulkan REQUIRED)

# <-- Link needed Libs: -->
target_link_libraries(${PROJECT_NAME}
    Vulkan::Vulkan 
    glfw
)
# <----------------------->