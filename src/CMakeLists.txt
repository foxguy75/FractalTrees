add_executable( SDLTree main.cxx )

target_include_directories( SDLTree PUBLIC 
    "${PROJECT_BINARY_DIR}"
    )

target_link_libraries( SDLTree ${CONAN_LIBS} )
