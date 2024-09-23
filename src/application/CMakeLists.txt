add_subdirectory( subsystem )

add_library( Application Application.cxx Application.hxx sprite_atlas.hxx sprite_atlas.cxx )

set_property(TARGET Application PROPERTY CXX_STANDARD 20)

find_package( SDL2 REQUIRED )
find_package( SDL2_ttf REQUIRED )
find_package( fmt REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( RapidJSON REQUIRED )

target_include_directories( Application PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/application"
    "${PROJECT_SOURCE_DIR}/src/"
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf-static 
    fmt::fmt
    rapidjson
    )

target_link_libraries( Application rapidjson SDL2::SDL2 SDL2_ttf::SDL2_ttf-static SDL2_image::SDL2_image fmt::fmt Subsystem )