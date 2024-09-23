add_library( Subsystem Subsystem.cxx Subsystem.hxx )

set_property(TARGET Subsystem PROPERTY CXX_STANDARD 20)

find_package( SDL2 REQUIRED )
find_package( SDL2_ttf REQUIRED )
find_package( fmt REQUIRED )

target_include_directories( Subsystem PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/application/subsystem"
    SDL2::SDL2 
    SDL2_ttf::SDL2_ttf-static 
    fmt::fmt
    )

target_link_libraries( Subsystem SDL2::SDL2 SDL2_ttf::SDL2_ttf-static fmt::fmt )