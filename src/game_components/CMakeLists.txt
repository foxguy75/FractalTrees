add_library( Components card.hxx card.cxx deck.hxx deck.cxx )

find_package( fmt REQUIRED )
find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )

set_property(TARGET Components PROPERTY CXX_STANDARD 20)

target_include_directories( Components PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/game_components"
    "${PROJECT_SOURCE_DIR}/src/application"
    SDL2::SDL2 
    fmt::fmt
    SDL2_image::SDL2_image
    )

target_link_libraries( Components SDL2::SDL2 fmt::fmt SDL2_image::SDL2_image )
