add_executable( SDLTree main.cxx )

target_include_directories( SDLTree PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/lib/fmt/include"
    )

target_link_libraries( SDLTree fmt ${CONAN_LIBS} )
