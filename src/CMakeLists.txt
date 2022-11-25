add_executable( SDLTree main.cxx )

set_property(TARGET SDLTree PROPERTY CXX_STANDARD 17)

target_include_directories( SDLTree PUBLIC 
    "${PROJECT_BINARY_DIR}"
    )

target_link_libraries( SDLTree ${CONAN_LIBS} )
