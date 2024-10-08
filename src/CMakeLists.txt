add_subdirectory(application)
add_subdirectory(game_components)

add_executable( ${PROJECT_NAME} main.cxx )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

find_package( SDL2 REQUIRED )
find_package( SDL2_ttf REQUIRED )
find_package( fmt REQUIRED )

target_include_directories( ${PROJECT_NAME} PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    SDL2::SDL2 
    SDL2_ttf::SDL2_ttf-static 
    fmt::fmt
    )

target_link_libraries( ${PROJECT_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf-static fmt::fmt Subsystem Application Components )
