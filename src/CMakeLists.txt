cmake_minimum_required(VERSION 3.0.0)

file(GLOB_RECURSE SRC_CXX_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE SRC_C_FILES CONFIGURE_DEPENDS *.c)
file(GLOB_RECURSE INC_CXX_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.cpp)
file(GLOB_RECURSE INC_C_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.c)

file(GLOB_RECURSE Walnut ${PROJECT_SOURCE_DIR}/external/Walnut/Walnut/src/Walnut/*.cpp)

# Add source files to be compiled here
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
     add_executable(${PROJECT_NAME}
          ${SRC_CXX_FILES}
          ${SRC_C_FILES}
          ${INC_CXX_FILES}
          ${INC_C_FILES}

          ${Walnut}
     )

else()
     add_executable(${PROJECT_NAME} WIN32
          ${SRC_CXX_FILES}
          ${SRC_C_FILES}
          ${INC_CXX_FILES}
          ${INC_C_FILES}

          ${Walnut}
     )
endif()

if(NOT CMAKE_GENERATOR_PLATFORM)
    set(MANUAL_MOVE TRUE)
    message(STATUS "Assuming platform on build")
endif(NOT CMAKE_GENERATOR_PLATFORM)

if(NOT MANUAL_MOVE)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM} # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
    )
endif(NOT MANUAL_MOVE)

if(UNIX AND NOT APPLE)
    if(MANUAL_MOVE)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_SOURCE_DIR}/bin/linux
        )

        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            ${CMAKE_SOURCE_DIR}/bin/linux # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
        )
    endif(MANUAL_MOVE)

    # Delete Cmake files
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_SOURCE_DIR}/bin/linux/CMakeFiles
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/Makefile
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/cmake_install.cmake
    )

elseif(APPLE)
    if(MANUAL_MOVE)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_SOURCE_DIR}/bin/mac
        )

        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            ${CMAKE_SOURCE_DIR}/bin/mac # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
        )
    endif(MANUAL_MOVE)

    # Delete Cmake files
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_SOURCE_DIR}/bin/mac/CMakeFiles
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/mac/Makefile
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/mac/cmake_install.cmake
    )

elseif(WIN32)
    if(MANUAL_MOVE)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
            ${CMAKE_SOURCE_DIR}/bin/win32
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            ${CMAKE_SOURCE_DIR}/bin/win32 # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
        )
    endif(MANUAL_MOVE)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)