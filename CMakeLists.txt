# Set CMake version number
cmake_minimum_required(VERSION 3.16)

# Change "Walnut-CMake" to your project name
project(Walnut-CMake VERSION 0.2.0 LANGUAGES CXX)

#----------------------------------------------------------------------------------------------
# Part till line 46 is taken from @lefticus

# set a default CXX standard used by the external tools like clang-tidy, cppcheck, etc.
# You can later set fine-grained standards for each target using `target_compile_features`
set(CMAKE_CXX_STANDARD 20)

### Add project_options
# include(FetchContent)
# FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/heads/main.zip)
# FetchContent_MakeAvailable(_project_options)
# include(${_project_options_SOURCE_DIR}/Index.cmake)
include(CMakeSetupFiles/Index.cmake)

# run_vcpkg()

# Initialize project_options
# uncomment the options to enable them
project_options(
#   ENABLE_CACHE
#   ENABLE_CONAN
  WARNINGS_AS_ERRORS
#   ENABLE_CPPCHECK
#   ENABLE_CLANG_TIDY
#   ENABLE_INCLUDE_WHAT_YOU_USE
#   ENABLE_COVERAGE
#   ENABLE_PCH
#   PCH_HEADERS <Eigen/Dense> <fmt/core.h> <vector> <utility> <string> <string_view>
#   ENABLE_DOXYGEN
#   ENABLE_IPO
#   ENABLE_USER_LINKER
#   ENABLE_BUILD_WITH_TIME_TRACE
#   ENABLE_UNITY
#   ENABLE_SANITIZER_ADDRESS
#   ENABLE_SANITIZER_LEAK
#   ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
#   ENABLE_SANITIZER_THREAD
#   ENABLE_SANITIZER_MEMORY
  CLANG_WARNINGS "-Weverything"
)

#----------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------
# Part till line 74 is very very similar to that of @codetechandtutorials

#           DOWNLOAD ALL THE SUBMODULES

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        if (1)
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        else()
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote --merge
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        endif()
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#----------------------------------------------------------------------------------------------



# Add locations of other CMakelists.txt (one per call)
add_subdirectory(
    src
)

# Comment these 2 out if you don't intend on using CTests
include(CTest)
enable_testing()


add_subdirectory(
    external/Walnut/vendor/glm
)

# The glfw submodule that is included in the Walnut project is not compatible with CMake for some reason
add_subdirectory(
    external/glfw
)

# Extra C++ specific option I need
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# <-- Set standard here -->
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
# <----------------------->

# <-- Comment out if you don't need CPack -->
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# <----------------------------------------->

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

# <-- Add directories to include directory here: -->
target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC external/glfw/include
    PUBLIC external/Walnut/vendor/glm
    PUBLIC external/Walnut/vendor/imgui
    PUBLIC external/Walnut/vendor/stb_image
    PUBLIC external/Walnut/Walnut/src
    PUBLIC $ENV{VULKAN_SDK}/include
    PUBLIC ${Vulkan_INCLUDE_DIRS}
)
# <------------------------------------------------>

# <-- Added directory of external libs to link here: -->
target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
)

find_package(Vulkan REQUIRED)

# <-- Link needed Libs: -->
target_link_libraries(${PROJECT_NAME}
    glfw Vulkan::Vulkan ${VULKAN_LIB_LIST} ${Vulkan_LIBRARY}
)
# <----------------------->