cmake_minimum_required(VERSION 3.10)

add_library(OLC
    "olcPixelGameEngine.cpp"
    )

target_include_directories(OLC PUBLIC
        "${PROJECT_SOURCE_DIR}/source/libs/olcPixelGameEngine")

#add_subdirectory(box2d_olc)
add_subdirectory(box2d)
