cmake_minimum_required(VERSION 3.10)
project(test_f2src)

set(CMAKE_CXX_STANDARD 17)

set(FMT_SOURCE_FILES ../fmt/core.h ../fmt/format.cc ../fmt/format.h ../fmt/format-inl.h ../fmt/ostream.h ../fmt/posix.cc ../fmt/posix.h ../fmt/printf.h ../fmt/ranges.h ../fmt/time.h)
set(SOURCE_FILES test_main.cpp ../AssetParser.cpp ../AssetParser.h ../AssetNamespace.cpp ../AssetNamespace.h ../AssetContainer.cpp ../AssetContainer.h ../MappingItem.cpp ../MappingItem.h ../AssetGeneratorConfig.h)
add_executable(test_f2src ${SOURCE_FILES} ${FMT_SOURCE_FILES})

if(LINUX)
    target_link_libraries(test_f2src stdc++fs)
else()

    if(MSVC)
        message("Using MSVC")
    else()
        message("Using MINGW")
        target_link_libraries(test_f2src stdc++fs)
    endif()
endif()