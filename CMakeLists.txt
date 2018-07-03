cmake_minimum_required(VERSION 3.10)
project(f2src)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


set(CMAKE_CXX_STANDARD 17)

set(FMT_SOURCE_FILES fmt/core.h fmt/format.cc fmt/format.h fmt/format-inl.h fmt/ostream.h fmt/posix.cc fmt/posix.h fmt/printf.h fmt/ranges.h fmt/time.h)
set(SOURCE_FILES main.cpp AssetParser.cpp AssetParser.h AssetNamespace.cpp AssetNamespace.h AssetContainer.cpp AssetContainer.h MappingItem.cpp MappingItem.h)

add_executable(f2src ${SOURCE_FILES} ${FMT_SOURCE_FILES})

message(${CMAKE_BUILD_TYPE})

if(UNIX AND NOT APPLE)
    set(LINUX 1)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
elseif(APPLE)
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 1)
    set(MSVC 0)
    set(MINGW 0)
elseif(WIN32)
    set(LINUX 0)
    set(WINDOWS 1)
    set(APPLE 0)
    if(MSVC)
        set(MSVC 1)
        set(MINGW 0)
    elseif(MINGW)
        set(MINGW 1)
        set(MSVC 0)
    endif()
else()
    set(LINUX 0)
    set(WINDOWS 0)
    set(APPLE 0)
    set(MSVC 0)
    set(MINGW 0)
endif()

configure_file (
        "${PROJECT_SOURCE_DIR}/AssetGeneratorConfig.h.in"
        "${PROJECT_SOURCE_DIR}/AssetGeneratorConfig.h"
)

# if(NOT LINUX) should work, too, if you need that
if(LINUX)
    message(STATUS ">>> Linux")
    target_link_libraries(f2src stdc++fs)
else()
    message(STATUS ">>> Not Linux")

    if(MSVC)

    else()
        target_link_libraries(f2src stdc++fs)
    endif()
    # stuff that should happen not on Linux
endif()

add_subdirectory(tests)
