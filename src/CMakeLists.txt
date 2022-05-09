cmake_minimum_required (VERSION 3.0.0)

# Add source files to be compiled here
if(MSVC)

     if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")


     add_executable(${PROJECT_NAME} 
          Main.cpp

          ../external/Walnut/Walnut/src/Walnut/Application.cpp
          ../external/Walnut/Walnut/src/Walnut/Image.cpp
          ../external/Walnut/Walnut/src/Walnut/Random.cpp
          ../external/Walnut/Walnut/src/Walnut/ImGui/ImGuiBuild.cpp

          ../external/Walnut/vendor/imgui/imgui_draw.cpp
          ../external/Walnut/vendor/imgui/imgui_demo.cpp
          ../external/Walnut/vendor/imgui/imgui_tables.cpp
          ../external/Walnut/vendor/imgui/imgui_widgets.cpp
          ../external/Walnut/vendor/imgui/imgui.cpp

     )

     else()

     add_executable(${PROJECT_NAME} WIN32
          Main.cpp

          ../external/Walnut/Walnut/src/Walnut/Application.cpp
          ../external/Walnut/Walnut/src/Walnut/Image.cpp
          ../external/Walnut/Walnut/src/Walnut/Random.cpp
          ../external/Walnut/Walnut/src/Walnut/ImGui/ImGuiBuild.cpp

          ../external/Walnut/vendor/imgui/imgui_draw.cpp
          ../external/Walnut/vendor/imgui/imgui_demo.cpp
          ../external/Walnut/vendor/imgui/imgui_tables.cpp
          ../external/Walnut/vendor/imgui/imgui_widgets.cpp
          ../external/Walnut/vendor/imgui/imgui.cpp

     )

     endif()

else()

     add_executable(${PROJECT_NAME}
          Main.cpp
     )

endif()



if(NOT MSVC)

     # Copy Binary to DEV specified location
     add_custom_command(
          TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
               ${CMAKE_SOURCE_DIR}/bin/
     )

     # # Set a symbolic link so the binary can find a required relative folder
     # set(link_src "${CMAKE_SOURCE_DIR}/assets")
     # if(UNIX AND NOT APPLE) 
     #     set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/../assets") 
     # else() 
     #     set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/../assets") 
     # endif() 

     # add_custom_command( 
     #     TARGET ${PROJECT_NAME} POST_BUILD
     #     COMMAND ${CMAKE_COMMAND} -E create_symlink ${link_src} ${link_dst} 
     #     DEPENDS ${link_dst} 
     #     COMMENT "symbolic link ${link_src} => ${link_dst}" 
     # )

     else()

     add_custom_command(
          TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
          ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.exe
          ${CMAKE_SOURCE_DIR}/bin/
     )

endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)