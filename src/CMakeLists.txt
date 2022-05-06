cmake_minimum_required (VERSION 3.0.0)

# adding all files needed to compile the project
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

if(NOT MSVC)

     # Copy Binary to DEV specified location
     add_custom_command(
          TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
               ${CMAKE_SOURCE_DIR}/bin/
     )

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
          ${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}.exe
          ${CMAKE_SOURCE_DIR}/bin/
     )

endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)