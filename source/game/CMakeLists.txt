cmake_minimum_required(VERSION 3.10)

add_library(GameEngine
        "GameEngine.cpp"
        "Renderer.cpp"
        )

target_include_directories(GameEngine PUBLIC
        "${PROJECT_SOURCE_DIR}/source/game"
        )

target_link_libraries(GameEngine PUBLIC
                      OLC
                      box2d
                      #box2d_olc
                      )

add_executable(Game
            "main.cpp"
            )

target_link_libraries(Game
        GameEngine)