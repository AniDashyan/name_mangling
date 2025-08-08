cmake_minimum_required(VERSION 3.10)
project(name_mangling)

set(CMAKE_CXX_STANDARD 17)

add_library(objlib OBJECT main.cpp)

add_executable(main $<TARGET_OBJECTS:objlib>)

if (MSVC)
    # For MSVC, use dumpbin on object file
    add_custom_target(inspect_symbols ALL
        COMMAND ${CMAKE_COMMAND} -E echo " Using dumpbin to inspect symbols..."
        COMMAND dumpbin /SYMBOLS $<TARGET_OBJECTS:objlib> | findstr Foo || cmd /c exit 0
        COMMENT " Inspecting symbols with dumpbin on object file"
        VERBATIM
    )
elseif(WIN32)
    # For MinGW or other Windows compilers, use nm
    add_custom_target(inspect_symbols ALL
        COMMAND ${CMAKE_COMMAND} -E echo "🔍 Using nm to inspect symbols..."
        COMMAND nm $<TARGET_OBJECTS:objlib> | findstr Foo || cmd /c exit 0
        COMMENT "🔧 Inspecting symbols with nm on object file"
        VERBATIM
    )
else()
    # On Linux/macOS, use nm on the final binary
    add_custom_target(inspect_symbols ALL
        COMMAND ${CMAKE_COMMAND} -E echo " Using nm to inspect symbols..."
        COMMAND nm $<TARGET_FILE:main> | grep Foo || true
        COMMENT "🔧 Inspecting symbols with nm on executable"
        VERBATIM
    )
endif()

# Ensure symbol inspection runs after the main target is built
add_dependencies(inspect_symbols main)
