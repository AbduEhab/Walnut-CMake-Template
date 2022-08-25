cmake_minimum_required(VERSION 3.0.0)

file(GLOB SRC_CXX_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB SRC_C_FILES CONFIGURE_DEPENDS *.c)
file(GLOB INC_CXX_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.cpp)
file(GLOB INC_C_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.c)

file(GLOB_RECURSE Walnut ${PROJECT_SOURCE_DIR}/external/Walnut/Walnut/src/Walnut/*.cpp)

# Add source files to be compiled here
if(WIN32)
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

else()
     add_executable(${PROJECT_NAME}
          ${SRC_CXX_FILES}
          ${SRC_C_FILES}
          ${INC_CXX_FILES}
          ${INC_C_FILES}
     )
endif()

message(STATUS `CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}`)

if(WIN32) # < - Windows Binary copy - >
     if(MSVC)
          # Copy Binary to DEV specified location
          add_custom_command(
               TARGET ${PROJECT_NAME} POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy
               ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.exe
               ${CMAKE_SOURCE_DIR}/bin/
          )
     else()
          add_custom_command(
               TARGET ${PROJECT_NAME} POST_BUILD
               COMMAND ${CMAKE_COMMAND} -E copy
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe
               ${CMAKE_SOURCE_DIR}/bin/
          )
     endif()

else() # < - UNIX Binary copy - >
     add_custom_command(
          TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
          ${CMAKE_SOURCE_DIR}/bin/
     )
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)