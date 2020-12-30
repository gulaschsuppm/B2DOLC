cmake_minimum_required(VERSION 3.10)

add_library(box2d_olc
    "../../game/Renderer.cpp"
    )

target_include_directories(box2d_olc PUBLIC
    "${PROJECT_SOURCE_DIR}/source/libs/box2d_olc"
    )

target_link_libraries(box2d_olc PUBLIC
    box2d,
    OLC
    )
