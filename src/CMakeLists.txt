add_library( Subsystem Subsystem.cxx Subsystem.hxx )
add_library( Application Application.cxx Application.hxx )
add_executable( SDLTree main.cxx TreeNode.hxx )

set_property(TARGET Subsystem PROPERTY CXX_STANDARD 20)
set_property(TARGET Application PROPERTY CXX_STANDARD 20)
set_property(TARGET SDLTree PROPERTY CXX_STANDARD 20)

target_include_directories( SDLTree PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    )

target_include_directories( Subsystem PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    )

target_include_directories( Application PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src"
    )

target_link_libraries( Application ${CONAN_LIBS} Subsystem )

target_link_libraries( SDLTree ${CONAN_LIBS} Subsystem Application )
