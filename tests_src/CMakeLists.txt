cmake_minimum_required(VERSION 3.16.3)

if (POLICY CMP0138)
    cmake_policy(SET CMP0138 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# Nombre del proyecto
project(DuckGameTests
    VERSION 0.0.0
    LANGUAGES CXX
)

# Intentar encontrar Google Test primero
find_package(GTest QUIET)

if (NOT GTEST_FOUND)
    # Si no se encontró, descarga y compila Google Test
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Agregar todos los archivos de prueba a una lista
set(TEST_SOURCES
    test_main.cpp
    test_position.cpp
    ../server_src/game_model/position.cpp # Asegúrate de que el nombre del archivo sea correcto
    ../server_src/game_model/duck.cpp
    ../server_src/game_model/armor.cpp
    ../server_src/game_model/weapon/weapon.cpp
    ../server_src/game_model/helmet.cpp
    ../server_src/game_model/game.cpp
    ../server_src/game_model/map_game.cpp
    ../server_src/game_model/positionable.h
    test_game.cpp
    test_duck.cpp
)

# Crear un ejecutable para las pruebas
add_executable(runTests ${TEST_SOURCES})

# Enlazar Google Test y otras bibliotecas necesarias
target_link_libraries(runTests GTest::gtest GTest::gtest_main)

# Opcional: Si deseas que se ejecuten las pruebas automáticamente al compilar
enable_testing()
add_test(NAME runTests COMMAND runTests)