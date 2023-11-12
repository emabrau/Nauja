cmake_minimum_required(VERSION 3.10)
project(v1.0)

set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


set(SOURCE_FILES
    main.cpp
    data.cpp
    functions.cpp
)

add_executable(EB ${SOURCE_FILES})

set_source_files_properties(CMakeCXXCompilerId.cpp PROPERTIES COMPILE_FLAGS -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY)
